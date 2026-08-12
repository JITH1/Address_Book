#ifndef CONTACT_H
#define CONTACT_H

#define RED    "\033[31m"
#define YELLOW "\033[33m"
#define GREEN  "\033[32m"
#define RESET  "\033[0m"

#define MAX_COUNT 100

#define NAME  1
#define PHONE 2 
#define MAIL  3


typedef struct 
{
    char phone[14];
    char name[40];
    char mail[40];
}Contact;

typedef struct
{
    Contact Contacts[MAX_COUNT];
    int ContactCount ;
}AddressBook;

enum flag
{
    FAILURE = 0,
    SUCCESS
};

/* Main Functions */
int create_contact(AddressBook *addressBook ,int Count_Max);
int edit_contact(AddressBook *addressBook);
int search_contact(AddressBook *addressBook);
void view_contact(AddressBook *addressBook);
int delete_contact(AddressBook *addressBook);

/* Validations */
int enter_phone(char *phone);
int enter_mail(char *mail);
int enter_name(char *name);
int duplicate(char *buff,int type,AddressBook *addressBook);
int Search_match(AddressBook *addressBook , int op , char *buffer);

#endif

