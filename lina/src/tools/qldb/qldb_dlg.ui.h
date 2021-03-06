/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qtextedit.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <qstring.h>
#include <ldatabase.h>
#include <ldefault.h>
#include <vector>

using namespace std;
using namespace LINA;

QDir root;
ID* current_LID=NULL;

void QLDB::open_database_root()
{
  //get a existing Directory and assign it to root
  QDir old_root = root;
  root = QFileDialog::getExistingDirectory();

  if(!root.path().isEmpty())
  {

  //Clear all database-roots
  DB.Clear();
  //Add database root
  DB.AddRoot(root.path().latin1());

  listView->clear();
  //get the catalogs in the database root and assign them to catalogs
  QStringList catalogs = root.entryList(QDir::Dirs);
  for ( QStringList::Iterator it = catalogs.begin(); it != catalogs.end(); ++it )
  {
    //is it really a catalog
    if(*it != "." && *it != "..")
    {
      //insert a QListViewItem for the catalog
      QListViewItem* catalog_item = new QListViewItem(listView,*it);
      //the catalog_item could have child items
      catalog_item->setOpen( true );
      //get a list of tokens in the catalog
      QStringList tokens = QDir(root.path()+"/"+*it).entryList(QDir::Files);
      for ( QStringList::Iterator s_it = tokens.begin(); s_it != tokens.end(); ++s_it )
      {
        //create a QListViewItem for each token at its catalog
        (void) new QListViewItem(catalog_item,*s_it);
      }
    }
  }

  //read the priority
  QFile priofile(root.path()+"/prio");
  priofile.open( IO_ReadOnly );
  QString tmp;
  priofile.readLine(tmp,10);
  priofile.close();
  int prio = tmp.toInt();
  
  spinBox_prio->setValue(prio);
  DB.SetWriteFlag(prio);
  }
  else
  {
  root = old_root;
  }
}

void QLDB::open_LID( QListViewItem* item )
{
  if(item && item->parent())
  {
    //reset the table content
    table->setNumCols(1);
    table->setNumRows(0);

    std::set<string> keys;
    table->setNumRows(DB.GetKeys(ID(item->parent()->text(0).latin1(),item->text(0).latin1()),keys));
    int i=0;
    for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it,++i)
    {
      //insert the key into the table
      table->setItem( i, 0, new QTableItem( table, QTableItem::OnTyping, (*it).c_str() ));

      //read the key's value array and assign it to value_vector
      vector<string> value_vector;
      DB.ReadArray(ID(item->parent()->text(0).latin1(),item->text(0).latin1()),(*it),value_vector);
      int y=1;
      for(vector<string>::iterator s_it = value_vector.begin(); s_it != value_vector.end(); ++s_it,++y)
      {
        //do we have enough columns
        if(table->numCols() <= y)
        {
          table->insertColumns(table->numCols());
        }
        //insert the value into the table
        table->setItem( i, y, new QTableItem( table, QTableItem::OnTyping, (*s_it).c_str() ));
      }

      table->adjustRow(i);
    }
    for(int i=0; i<table->numCols();++i)
    {
      table->adjustColumn(i);
    }

    //label_LID shows wich LID is currently open
    label_LID->setText("LID - Catalog: "+item->parent()->text(0)+" Token: "+item->text(0));
    //update current_LID
    delete current_LID;
    current_LID = new ID(item->parent()->text(0).latin1(),item->text(0).latin1());
  }
}

void QLDB::save_LID()
{
  if(current_LID)
  {

    for(int i=0;i != table->numRows(); ++i)
    {
      //do we have a key here
      if(!table->text(i,0).isEmpty())
      {
        //push the values to value_vector
        vector<string> value_vector;
        for(int y=1; y <= table->numCols(); ++y)
        {
          if(!table->text(i,y).isEmpty())
          {
            value_vector.push_back(table->text(i,y).latin1());
          }
        }

        //write the array of the current key to the LID
        DB.WriteArray(*current_LID,table->text(i,0).latin1(),value_vector);
      }
    }
  }
}

void QLDB::create_catalog()
{
  //get a new catalog name from a QInputDialog
  QString catalog_name = QInputDialog::getText("Create catalog","Name");
  //make sure the user set a name
  if(!catalog_name.isEmpty())
  {
    //create the directory for the new catalog
    //and insert it in the right place on the
    //QListView
    QDir(root.path()).mkdir(catalog_name);
    new QListViewItem(listView,catalog_name);
  }
}

void QLDB::set_prio( int )
{
  //make sure a root is set
  if(root.path().length())
  {
    QFile prio(root.path()+"/prio");
    //open the prio file for writing
    prio.open( IO_WriteOnly );
    //put the priority into it
    prio.writeBlock(QString::number(spinBox_prio->value()).latin1(),QString::number(spinBox_prio->value()).length());
    //close
    prio.close();
  }
}

void QLDB::new_LID()
{
  if(listView->currentItem())
  {
    QString catalog;
    //assign catalog the current catalog
    if(listView->currentItem()->parent())
    {
      catalog = listView->currentItem()->parent()->text(0);
    }
    else
    {
      catalog = listView->currentItem()->text(0);
    }

    //Ask the user for a token
    QString token = QInputDialog::getText("Type the token of the new LID","Token");

    //did he give us one
    if(!token.isEmpty())
    {
      //create a file for the new LID
      QFile file(root.path()+"/"+catalog+"/"+token);
      file.open( IO_WriteOnly );
      file.close();

      //insert a QListViewItem for the new LID
      QListViewItem* the_new_LID;
      if(listView->currentItem()->parent())
      {
        the_new_LID = new QListViewItem(listView->currentItem()->parent(),token);
      }
      else
      {
        the_new_LID = new QListViewItem(listView->currentItem(),token);
      }

      //open the new LID
      open_LID(the_new_LID);
    }
  }
}

void QLDB::add_key_row()
{
  //simply insert a new row at the last row
  table->insertRows(table->numRows());
}

void QLDB::add_value_column()
{
  //simply insert a new column at the last column
  table->insertColumns(table->numCols());
}


void QLDB::import_template()
{
  if(!root.path().isEmpty() && current_LID != NULL )
  {
    QString filename = QFileDialog::getOpenFileName(
                         root.path()+"/templates/",
                         QString::null,
                         this,
                         "Import template dialog",
                         "Choose a template to import" );
    if(filename != QString::null)
    {
    QFileInfo fi(filename);
    filename = fi.fileName();
    ID template_LID("templates",filename.latin1());

    std::set<string> keys;
    int i=table->numRows();
    table->setNumRows(table->numRows() + DB.GetKeys(template_LID,keys));
    for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it,++i)
    {
      //insert the key into the table
      table->setItem( i, 0, new QTableItem( table, QTableItem::OnTyping, (*it).c_str() ));

      //read the key's value array and assign it to value_vector
      vector<string> value_vector;
      DB.ReadArray(template_LID,(*it),value_vector);
      int y=1;
      for(vector<string>::iterator s_it = value_vector.begin(); s_it != value_vector.end(); ++s_it,++y)
      {
        //do we have enough columns
        if(table->numCols() <= y)
        {
          table->insertColumns(table->numCols());
        }
        //insert the value into the table
        table->setItem( i, y, new QTableItem( table, QTableItem::OnTyping, (*s_it).c_str() ));
      }

      table->adjustRow(i);
    }
    for(int i=0; i<table->numCols();++i)
    {
      table->adjustColumn(i);
    }
   }
  }
}


void QLDB::show_source()
{
if(current_LID)
{
 string source;
 DB.ReadPlainText(*current_LID,source);
 QDialog source_viewer(this,"Show source");
 QTextEdit source_textedit(&source_viewer,"hmm");
 source_textedit.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
 source_textedit.setWordWrap(QTextEdit::NoWrap);
 source_viewer.setGeometry(200,200,500,400);
 source_viewer.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
 source_textedit.setGeometry(0,0,500,400);
 source_textedit.setText(source.c_str());
 source_textedit.setReadOnly(true);
 source_viewer.exec();
 }
}
