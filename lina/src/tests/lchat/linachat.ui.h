/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <iostream>
#include <vector>
#include <qtimer.h>
#include <ldefault.h>

LClient client;
std::vector<std::string> history;
QTimer *timer;

void LINAChat::send_message()
{
  if(chat_input->text().find("/server") == 0)
  {
    chat_textedit->append("<font color=\"yellow\">Trying to connect to "+chat_input->text().section(" ",1).simplifyWhiteSpace()+"</font>\n");
    QString server_to_connect(chat_input->text().section(" ",1).simplifyWhiteSpace());
    
    client.ConnectTo(server_to_connect);
  }
  else
  {
    client.SendPackage(LNetPackage(LNetMessage,chat_input->text() ));
  }
  history.push_back(chat_input->text());
  chat_input->clear();
}


void LINAChat::set_nick( std::string new_nick )
{
  nickname_label->setText(new_nick);
}

void LINAChat::init()
{
  timer = new QTimer(this);
  connect( timer, SIGNAL(timeout()), this, SLOT(receive_messages()) );
  timer->start( 200); // 0.2 seconds interval timer
}


void LINAChat::receive_messages()
{
  LNetPackage tmp;
  client.ReceivePackage(tmp);
  if(tmp.buffer != NULL)
    chat_textedit->append(QString(tmp.buffer) + "\n");

}


void LINAChat::set_server(std::string server)
{
  client.ConnectTo(server);
}
