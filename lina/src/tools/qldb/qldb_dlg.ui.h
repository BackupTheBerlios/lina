/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qfiledialog.h>
#include <qinputdialog.h>
#include <qstring.h>
#include <ldatabase.h>
#include <vector>

QDir root;
LID* current_LID=NULL;

void QLDB::open_database_root()
{
  //get a existing Directory and assign it to root
  root = QFileDialog::getExistingDirectory();

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
  int prio = priofile.getch() - 48;
  priofile.close();
  spinBox_prio->setValue(prio);
}

void QLDB::open_LID( QListViewItem* item )
{
  if(item && item->parent())
  {
    //reset the table content
    table->setNumCols(1);
    table->setNumRows(0);

    LDatabase db;
    db.AddRoot(root.path().latin1());

    std::vector<string> keys;
    table->setNumRows(db.GetKeys(LID(item->parent()->text(0),item->text(0).latin1()),keys));
    int i=0;
    for(vector<string>::iterator it = keys.begin(); it != keys.end(); ++it,++i)
    {
      //insert the key into the table
      table->setItem( i, 0, new QTableItem( table, QTableItem::WhenCurrent, (*it) ));

      //read the key's value array and assign it to value_vector
      vector<string> value_vector;
      db.ReadArray(LID(item->parent()->text(0),item->text(0).latin1()),(*it),value_vector);
      int y=1;
      for(vector<string>::iterator s_it = value_vector.begin(); s_it != value_vector.end(); ++s_it,++y)
      {
        //do we have enough columns
        if(table->numCols() <= y)
        {
          table->insertColumns(table->numCols());
        }
	//insert the value into the table
        table->setItem( i, y, new QTableItem( table, QTableItem::WhenCurrent, (*s_it) ));
      }

      table->adjustRow(i);
    }
    for(int i=0; i<table->numCols();++i)
    {
      table->adjustColumn(i);
    }

    //label_LID shows wich LID is currently open
    label_LID->setText("LID - Catalog: "+item->parent()->text(0)+" Token: "+item->text(0).latin1());
    //update current_LID
    delete current_LID;
    current_LID = new LID(item->parent()->text(0),item->text(0).latin1());
  }
}

void QLDB::save_LID()
{
  if(current_LID)
  {
    //create a LDatabase object and add the root
    LDatabase db;
    db.AddRoot(root.path().latin1());

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
        db.WriteArray(*current_LID,table->text(i,0).latin1(),value_vector);
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
  prio.putch(spinBox_prio->value() + 48);
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
