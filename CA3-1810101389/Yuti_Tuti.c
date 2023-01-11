#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "func.h"

void main(void)
{
    Init();
    while(1)
    {
        Get_Command();
        Reply_Command();
    }
}

void Init(void)
{
    User_Head = malloc(sizeof(user));
    User_Head->next = NULL;
    Current_User = NULL;
}