#include<stdio.h>
#include "File_handler.h"

int load_contact(AddressBook *addressBook)
{
    addressBook->ContactCount = 0 ;

    FILE *ptr = fopen("Database.csv","r");

    if(ptr == NULL)
    {
        perror(RED"\nCan't Load Data...!\n"RESET);
        return FAILURE ;
    }

    fscanf(ptr,"%d\n",&addressBook->ContactCount);

    for(int i = 0 ; i<addressBook->ContactCount ; i++)
    {
        fscanf(ptr,"%[^,],%[^,],%[^\n]\n",addressBook->Contacts[i].name,addressBook->Contacts[i].phone,addressBook->Contacts[i].mail);
    }

    fclose(ptr);

    // Sort Contacts

    return SUCCESS ;
}

int save_contact(AddressBook *addressBook)
{
    FILE *ptr = fopen("Database.csv","w");

    if(ptr == NULL)
    {
        perror(RED"\nCan't Save Data...!\n"RESET);
        return FAILURE;
    }
    
    fprintf(ptr,"%d\n",addressBook->ContactCount);

    for(int i = 0 ; i<addressBook->ContactCount ; i++)
    {
        fprintf(ptr,"%s,%s,%s\n",addressBook->Contacts[i].name,addressBook->Contacts[i].phone,addressBook->Contacts[i].mail);
    }

    fclose(ptr);

    return SUCCESS ;
    
}