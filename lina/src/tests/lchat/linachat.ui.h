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

using namespace LINA;

Client client;
std::vector<std::string> history;
QTimer *timer;

void LINAChat::send_message()
{
  if(chat_input->text().find("/server") == 0)
  {
    chat_textedit->append("<font color=\"yellow\">Trying to connect to "+chat_input->text().section(" ",1).simplifyWhiteSpace()+"</font>\n");
    QString server_to_connect(chat_input->text().section(" ",1).simplifyWhiteSpace());

    client.ConnectTo(server_to_connect.latin1());
    /*std::string test;
    std::cerr >> test;
    chat_textedit->append(QString(test) + "\n");*/
  }
  if(chat_input->text().find("/nick") == 0)
  {
    chat_textedit->append("<font color=\"yellow\">Change nick to "+chat_input->text().section(" ",1).simplifyWhiteSpace()+"</font>\n");
    QString new_nick(chat_input->text().section(" ",1).simplifyWhiteSpace());

    set_nick(new_nick);
    /*std::string test;
    std::cerr >> test;
    chat_textedit->append(QString(test) + "\n");*/
  }
  else
  {
    client.SendPackage(NetPackage(NetChatMessage,  Buffer(chat_input->text()) ));
  }
  history.push_back(chat_input->text().latin1());
  chat_input->clear();
}


void LINAChat::set_nick( QString new_nick )
{
  client.SetClientInfo(new_nick);
  nickname_label->setText(new_nick.latin1());
}

void LINAChat::init()
{
  timer = new QTimer(this);
  connect( timer, SIGNAL(timeout()), this, SLOT(receive_messages()) );
  timer->start( 200); // 0.2 seconds interval timer
}


void LINAChat::receive_messages()
{
  NetPackage tmp;
  while(client.ReceivePackage(tmp) != -1)
  {

    if(tmp.buffer.Size() > 0 && tmp.type == NetChatMessage)
      chat_textedit->append(QString(tmp.buffer.Get()) + "\n");
    else if(tmp.buffer.Size() > 0 && (tmp.type == NetClientInfo || tmp.type == NetRemoveClientInfo))
    {
      client.HandleClientInfo(tmp);
      people_list->clear();
      const std::set<ClientInfo>* client_infos = client.GetClientsInformation();
      for(std::set<ClientInfo>::iterator it = client_infos->begin(); it != client_infos->end(); ++it)
          people_list->insertItem(QString((*it).Nickname()));
    }

  }
}


void LINAChat::set_server(QString server)
{
  client.ConnectTo(server.latin1());
}
