#include<stdio.h>
#include "File_handler.h"

int main()
{

   int option ;
   AddressBook addressBook ;

   if(load_contact(&addressBook))
   {
      printf(GREEN"\nContact's Loaded Successfully...!\n"RESET);
   }
   else
   {
      printf(RED"\nLoading Contact Failed...!\n");
      return 0;
   }
 
   do
   {
      printf(YELLOW"\nAddress Book Menu : \n1.Create Contact\n2.Edit Contact\n3.Search Contact\n4.View Contact List\n5.Save Contact\n6.Delete Contact\n7.Exit Menu\n"RESET);  
      printf(YELLOW"\nEnter Your Option : \n"RESET);
      scanf("%d",&option);
      
      if(!(option>=0 && option<=7))
      {
         printf(RED"\nInvalid Option selected please Enter valid option and try Again...!\n"RESET);
         continue ;
      }

      switch(option)
      {
         case 1 :
         if(create_contact(&addressBook ,MAX_COUNT))
         printf(GREEN"\nContact Created Successfully...!\n"RESET);
         else
         printf(RED"\nCan't Create Contact...!\n"RESET);
         break;

         case 2 :
         break;

         case 3 :
         break;

         case 4 :
         view_contact(&addressBook);
         break;

         case 5 :
         if(save_contact(&addressBook))
         {
            printf(GREEN"\nContact Saved Successfully...!\n"RESET);

         }
         else
         {
             printf(RED"\nUnable To Save Conatacts....!\n"RESET);
         }
         break;
         
         case 6 :
         if(delete_contact(&addressBook) == SUCCESS)
         {
            printf(GREEN"\nContact Deleted Successfully...!\n"RESET);
         }
         else
         {
            printf(RED"Unable to Delete...!\n"RESET);
         }
         break;

         default :
         break;

      }

   }while(option!=7);

   return 0;
}
