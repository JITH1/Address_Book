#include<stdio.h>
#include"File_handler.h"
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int *ptr ;
int size ;
int set ;

int create_contact(AddressBook *addressBook ,int Count_Max)
{
    char phone[14] , mail[40] , name[40];
    int op ;

    if(addressBook->ContactCount >= MAX_COUNT)
    {
        printf(RED"\nAddress Book Full...!\n"RESET);
        return FAILURE ;
    }
    
    while(!enter_name(name))
    {
        printf(RED"\nInvalid Name Format...Please try again...!\n"RESET);
        printf("\nDo you want to continue ?\n1.Yes\n2.No\n");
        scanf("%d",&op);
        if(op == 2 )
        return FAILURE ;
        
    }

    while(!enter_phone(phone))
    {
        printf(RED"\nInvalid Phone Format...Please try again...!\n"RESET);
        printf("\nDo you want to continue ?\n1.Yes\n2.No\n");
        scanf("%d",&op);
        if(op == 2 )
        return FAILURE ;
    }

    while(!enter_mail(mail))
    {
        printf(RED"\nInvalid Email Format...Please try again...!\n"RESET);
        printf("\nDo you want to continue ?\n1.Yes\n2.No\n");
        scanf("%d",&op);
        if(op == 2 )
        return FAILURE ;
    }
    
    if(duplicate(mail,MAIL,addressBook) || duplicate(phone,PHONE,addressBook))
    {
        printf(RED"\nDuplicate Contact Found...!\n"RESET);
        return FAILURE ;
    }

    strcpy(addressBook->Contacts[addressBook->ContactCount].name,name);
    strcpy(addressBook->Contacts[addressBook->ContactCount].phone,phone);
    strcpy(addressBook->Contacts[addressBook->ContactCount].mail,mail);

    addressBook->ContactCount++; 

    sort_contact(addressBook);

    return SUCCESS ;
}

int search_contact(AddressBook *addressBook)
{
     if(addressBook->ContactCount == 0)
     {
         printf(RED"\nContact List Empty...!\n");
         return FAILURE ;
     }

    char buffer[40] ;
    int n , m ;

    retry :
    printf("\nSearch Contact by  \n1.Name\n2.Phone\n3.Mail\nEnter your choice : \n");
    scanf("%d",&n);

    if(!(n>0 && n<4))
    {
        printf(RED"\nInvalid Option...please enter valid option...!\nDo You wish to continue...!(Y/N) ?\n"RESET);
        char op ;
        scanf(" %c",&op);

        if(op == 'Y' || op == 'y')
        {
            goto retry ;
        }
        else if(op == 'n' || op == 'N')
        {
            return FAILURE ;
        }
        else
        {
            printf(RED"\nInvalid option expected (Y/N)...please try again...!\n"RESET);
            goto retry;
        }
        
    }
    
    
    (n == 1) ? printf("\nEnter the Name : \n") : (n == 2) ? printf("\nEnter the phone : \n") : printf("\nEnter the mail : \n"); ;
    (n == 1) ? scanf(" %39[^\n]",buffer) : (n == 2) ? scanf(" %39s",buffer) : scanf(" %39s",buffer) ;
    
     if(m = Search_match(addressBook , n , buffer))
     {
        printf(GREEN"\n%d Contacts Match found...!\n"RESET,m);
     }
     else
     {
        printf(RED"\nNo Match Found...!\n"RESET);
        return FAILURE;
     }
     
     return SUCCESS ;

}

void view_contact(AddressBook *addressBook)
{
    if(addressBook->ContactCount == 0)
    {
        printf(RED"\nContact List Empty...!\n"RESET);
        return;
    }

    printf(YELLOW"+-----+----------------------+----------------+-----------------------------+\n");
    printf("| S.No| Name                 | Phone          | Email                       |\n");
    printf("+-----+----------------------+----------------+-----------------------------+\n");

    for(int i = 0 ; i<addressBook->ContactCount ; i++)
    {
        printf("| %-3d | %-20s | %-14s | %-27s |\n",i+1, addressBook->Contacts[i].name,addressBook->Contacts[i].phone ,addressBook->Contacts[i].mail );
    }

    printf("+-----+----------------------+----------------+-----------------------------+\n"RESET);
}

int delete_contact(AddressBook *addressBook)
{
    
    if(addressBook->ContactCount == 0)
    {
        printf(RED"\nContact List is empty...!\n"RESET);
        return FAILURE ;
    }
    
    int n , m ;

    view_contact(addressBook);

    printf("\nSelect the S.No of Contact to delete contact : \n");
    scanf("%d",&n);

    printf("\nAre you sure you want to delete contact : \n\nS.No -> %d  : %-5s  %-5s %-5s\n\nEnter the S.No to confirm : \n",n,addressBook->Contacts[n-1].name,addressBook->Contacts[n-1].phone,addressBook->Contacts[n-1].mail);
    scanf("%d",&m);

    if(m != n)
    {
        printf(RED"\nIncorrect S.No Delete Contact Failed...!\n"RESET);
        return FAILURE ;
    }

    for(int i = n-1 ; i<addressBook->ContactCount ; i++)
    {
        addressBook->Contacts[i] = addressBook->Contacts[i+1];
    }

    addressBook->ContactCount--;

    return SUCCESS;
}

int enter_name(char *name)
{
    printf("\nEnter name : \n");
    scanf(" %39[^\n]",name);

    if(!isupper(name[0]))
    return FAILURE ;

    int flag = 0 ;

    for(int i = 1 ; name[i]!='\0' ; i++)
    {
        if(flag)
        {
           if(!(isupper(name[i])))
           return FAILURE ;
           
           flag = 0;
        }

        if(!isalpha(name[i]))
        {
           if(!(name[i] == ' '))
           {
               return FAILURE ;
           }

           flag++;
        }
    }

    return SUCCESS ;
} 

int edit_contact(AddressBook *addressBook)
{

    if(addressBook->ContactCount == 0)
    {
        printf(RED"\nContact List is Empty...!\n"RESET);
        return FAILURE ;
    }

    int n , m , flag = 0 ; 
    char buffer[40];

    ptr = malloc(sizeof(int)*addressBook->ContactCount);
    set = 1 ;
    size = 0 ;

    if(!(m = search_contact(addressBook)))
    {
        printf(RED"\nNo Contact Match Found...!\n"RESET);
        return FAILURE ;
    }

    printf("\nEnter the S.No to edit : \n");
    scanf("%d",&m);
    
    for(int i = 0 ; i<size ; i++)
    {
        if(m == ptr[i])
        flag++;
    }

    if(!flag)
    {
        printf(RED"\nInvalid S.No Of Matched Contect Entered...!\n"RESET);
        return FAILURE ;
    }
    
    free(ptr);
    set = 0 ;
    size = 0 ;

    Again :
    printf("\nEdit by \n1.Name\n2.Phone\n3.Email\nEnter Your Option : \n");
    scanf(" %d",&n);

    if(!(n>0 && n<4))
    {
        printf(RED"\nInvalid Option...please enter valid option...!\nDo You wish to continue...!(Y/N) ?\n"RESET);
        char op ;
        scanf(" %c",&op);

        if(op == 'Y' || op == 'y')
        {
            goto Again ;
        }
        else if(op == 'n' || op == 'N')
        {
            return FAILURE ;
        }
        else
        {
            printf(RED"\nInvalid option expected (Y/N)...please try again...!\n"RESET);
            goto Again;
        }
        
    }

    if(n == 1)
    {
        if(enter_name(buffer))
        {
            strcpy(addressBook->Contacts[m-1].name,buffer);
        }
        else
        {
            printf(RED"\nInvalid Name...!\n"RESET);
            return FAILURE ;
        }
    }
    else if(n == 2)
    {
        if(enter_phone(buffer) && (!duplicate(buffer,PHONE,addressBook)))
        {
            strcpy(addressBook->Contacts[m-1].phone,buffer);
        }
        else
        {
            printf(RED"\nInvalid Phone format / Duplicate phone...!\n"RESET);
            return FAILURE ;
        }
    }
    else if(n == 3)
    {
        if(enter_mail(buffer) && (!duplicate(buffer,MAIL,addressBook)))
        {
            strcpy(addressBook->Contacts[m-1].mail,buffer);
        }
        else
        {
            printf(RED"\nInvalid mail format / Duplicate mail...!\n"RESET);
            return FAILURE ;
        }
    }

    return SUCCESS ;

}

int enter_phone(char *phone)
{
    printf("\nEnter the phone number (+xx) add if Country Code: \n");
    scanf(" %13s",phone);

    if(!(strlen(phone)==13 || strlen(phone)==10))
    {
        return FAILURE ;
    }

    if(strlen(phone) == 13)
    {
        if(!(phone[0] == '+'))
        return FAILURE ;
    
        for(int i = 1; phone[i]!='\0' ; i++)
        {
            if(!(isdigit(phone[i])))
            return FAILURE ;
        }

        int n = phone[3] - '0' ;

        if(!(n>5 && n<=9))
        {
           return FAILURE ;
        }

    }
    else if(strlen(phone) == 10)
    {
        int n = phone[0] - '0' ;

        if(!(n>5 && n<=9))
        {
           return FAILURE ;
        }

        for(int i = 1; phone[i]!='\0' ; i++)
        {
            if(!(isdigit(phone[i])))
            return FAILURE ;
        }
    }
    else
    {
        return FAILURE ;
    }

    return SUCCESS ;
}

int enter_mail(char *mail)
{
    printf("\nEnter the mail : \n");
    scanf(" %39s",mail);

    if(!isalpha(mail[0]))
    return FAILURE ;

    int hash[2] = {0}; // 0 -> @ , 1 -> .

    for(int i = 1 ; mail[i]!='\0' ; i++)
    {
        if(!isalnum(mail[i]))
        {
            if(mail[i] == '@')
            {
                hash[0]++;
            }
            else if(mail[i] == '.')
            {
                hash[1]++;
            }
            else
            return FAILURE ;
        }
    
    }

    if(hash[0]>1 || hash[1]>1 || hash[1] == 0 || hash[0] == 0)
    {
        return FAILURE ;
    }

    int n = strcspn(mail,"@") , c = -1;

    for(int i = n ; mail[i]!='.' ; i++)
    {
        c++;
    }
    
    if(c == 0)
    {
        return FAILURE ;
    }
    
    return SUCCESS ; 
}

int duplicate(char *buff,int type,AddressBook *addressBook)
{
    if(type == MAIL)
    {
        for(int i = 0 ; i<addressBook->ContactCount ; i++)
        {
            if(strcmp(buff,addressBook->Contacts[i].mail) == 0)
            {
                return SUCCESS ;
            }
        }
    }
    else if(type == PHONE)
    {
        for(int i = 0 ; i<addressBook->ContactCount ; i++)
        {
            if(strcmp(buff,addressBook->Contacts[i].phone) == 0)
            {
                return SUCCESS ;
            }
        }
    }

    return FAILURE ;

}

int Search_match(AddressBook *addressBook , int op , char *buffer)
{
    int count = 0 ;
   
    if(op == NAME)
    {
        for(int i = 0 ; i<addressBook->ContactCount ; i++)
        { 
             if(strcmp(buffer,addressBook->Contacts[i].name) == 0)
             {
                  printf(YELLOW"\nS.No -> %-3d | %-20s | %-14s | %-27s |\n"RESET,i+1, addressBook->Contacts[i].name,addressBook->Contacts[i].phone ,addressBook->Contacts[i].mail );
                  count++;

                  if(set)
                    ptr[size++] = i+1;
             }   
        }

        return count ;

    }
    else if(op == PHONE)
    {
        for(int i = 0 ; i<addressBook->ContactCount ; i++)
        { 
             if(strcmp(buffer,addressBook->Contacts[i].phone) == 0)
             {
                printf(YELLOW"\nS.No -> %-3d | %-20s | %-14s | %-27s |\n"RESET,i+1, addressBook->Contacts[i].name,addressBook->Contacts[i].phone ,addressBook->Contacts[i].mail );
                count++;

                if(set)
                  ptr[size++] = i+1;
             }   
        }  

        return count ;
    }
    else if(op == MAIL)
    {
        for(int i = 0 ; i<addressBook->ContactCount ; i++)
        { 
             if(strcmp(buffer,addressBook->Contacts[i].mail) == 0)
             {
                printf(YELLOW"\nS.No -> %-3d | %-20s | %-14s | %-27s |\n"RESET,i+1, addressBook->Contacts[i].name,addressBook->Contacts[i].phone ,addressBook->Contacts[i].mail );
                count++;

                if(set)
                  ptr[size++] = i+1;
             }   
        }

        return count ;
    }

    return 0 ; 
}

void sort_contact(AddressBook *addressBook)
{

    for(int i = 0 ; i<addressBook->ContactCount - 1 ; i++)
    {
        int alph_order = i ;

        for(int j = i+1 ; j<addressBook->ContactCount ; j++)
        {
            if(addressBook->Contacts[j].name[0] < addressBook->Contacts[alph_order].name[0])
            {
                alph_order = j ;
            }
        }

        char buffer[40];

        strcpy(buffer,addressBook->Contacts[alph_order].name);
        strcpy(addressBook->Contacts[alph_order].name,addressBook->Contacts[i].name);
        strcpy(addressBook->Contacts[i].name,buffer);
    }
    
}