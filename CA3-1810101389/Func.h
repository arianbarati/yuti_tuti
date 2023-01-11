
void Get_Command(void)
{
    printf("\nInput Command:");
    Input_Text = malloc(500);
    gets(Input_Text);
    if(debug)printf("\nInput Text = %s\n" , Input_Text);
    if(strlen(Input_Text)<3)Command_Type = -1;
    else Command_Type = Distiguish_command_Type(strtok(Input_Text , " "));
    if(debug)printf("\nCommand = %c" , Command_Type);
}
void Posting(void)
{
    post *Temp;
    if(!Current_User)
    {
        printf("\nPlease login first.");
        return;
    }
    Temp = malloc(sizeof(post));
    Temp->text= Input_Text;
    Current_User->Post_Index++;
    Current_User->Post_Count++;
    Temp->post_id = Current_User->Post_Index;
    Temp->likes = 0;
    Temp->next = Current_User->posts->next;
    Current_User->posts->next = Temp;
    if(debug)
    {
        Temp = Current_User->posts->next;
        while(Temp)
        {
            printf("\nPost ID:%d  post: %s ",Temp->post_id,Temp->text);
            Temp = Temp->next;
        }
    }    
}

void like(void)
{
    if(!Current_User)
    {
        printf("Please login first.");
        return;
    }
    char *Param1 ;
    int Param2=0;
    if(strlen(Input_Text) > 0)
    {
        Param1 = strtok(Input_Text," ");
        Input_Text += strlen(Param1)+1;
    }
    if(strlen(Input_Text) > 0) 
    {
        Param2 = atoi(Input_Text);        
        if (Param2==0)
        {
            printf("wrong ID");
            return;
        }
    }    
    else
    {
        printf("\n Incorrect username or postid...");
        return;
    }
    user *Temp; 
    Temp = User_Head->next;
    while(Temp)
    {
        if(Compare_Two_Strings(Temp->username , Param1))
        {
            post *Temp2 = Temp->posts->next;
            while(Temp2)
            {
                if(debug)printf("\n COM %d , %d",Temp2->post_id,Param2);
                if(Temp2->post_id == Param2)
                {
                    Temp2->likes++;
                    printf("\nPost of the user:%s with post ID:%d liked." ,Param1, Param2);
                    return;
                }
                Temp2 = Temp2->next;
            }
        }
        Temp = Temp->next;
    }
    printf("\nPost not found.");
}

void Info(void)
{
    if(!Current_User)
    {
        printf("Please login first.");
        return;
    }
    printf("\nUsername:%s  " , Current_User->username);
    printf("Password:%s   Post No:%d" , Current_User->password,Current_User->Post_Count);
    post *Temp;
    Temp = Current_User->posts->next;
    while(Temp)
    {
        printf("\nUsername:%s  Post ID:%d  Likes:%d  Post:[%s]",Current_User->username,Temp->post_id, Temp->likes,Temp->text);
        Temp = Temp->next;
    } 
}

void Find_user(void)
{
    user *Temp;
    Temp = User_Head ->next;
    while(Temp)    
    {
        if(Compare_Two_Strings(Temp->username , Input_Text))
        {
            printf("\nUsername:%s  " , Temp->username);
            printf("  Post No:%d" , Temp->Post_Count);
            post *Temp2;
            Temp2 = Temp->posts->next;
            while(Temp2)
            {
                printf("\nPost ID:%d  Likes:%d  Post:[%s]",Temp2->post_id, Temp2->likes,Temp2->text);
                Temp2 = Temp2->next;
            }      
            return;      
        }
        Temp= Temp->next;
    }
    printf("\nUser not found...");
}

void Delete_post(void)
{
    if(!Current_User)
    {
        printf("please login first.");
        return;
    }
    post *Temp= Current_User->posts;
    while(Temp)
    {
        if(Temp->next->post_id == atoi(Input_Text))
        {
            Temp->next = Temp->next->next;        
            printf("Post deleted succesfully.");
            return;
        }
        Temp = Temp->next;
    }
    printf("post not found.");
    return;

}

void save(void)
{
    user *Temp;
    post *TempP;
    FILE* accounts = fopen("accounts.txt" , "w");
    if (accounts == NULL)
    {
        printf("\nError in creating <accounts.txt>");
        return;
    }
    FILE* fp = fopen("posts.txt" , "w");
    if (fp == NULL)
    {
        printf("\nError in creating <posts.txt>");
        return;
    }
    Temp = User_Head ->next;
    while(Temp)
    {
        fprintf(accounts,"%s %s %d\n",Temp->username,Temp->password,Temp->Post_Count);
        TempP = Temp->posts->next;
        while(TempP)
        {
            fprintf(fp,"%s %s %d\n",TempP->text,Temp->username,TempP->likes);
            TempP = TempP->next;
        }
        Temp = Temp->next;
    }
    fclose(accounts); 
    fclose(fp);
    printf("\nSave successfuly.");
}
void Reply_Command(void)
{
    switch(Command_Type)
    {
        case Sign_UP :
            SignUP();
        break;
        case LOG_IN:
            LogIN();
        break;
        case LOG_OUT :
            LogOUT();
        break;
        case POST:
            Posting();
        break;
        case LIKE:
            like();
        break;
        case DELETE_POST:
            Delete_post();
        break;
        case INFO:
            Info();
        break;
        case FIND_USER:
            Find_user();
        case SAVE:
            save();
        break;

        default:
        printf("Unknown Command\n");
    } 
    free(Input_Text);
}

void SignUP(void)
{
    char *Param1,*Param2;
    user *Temp;
    if(strlen(Input_Text) > 0)
    {
        Param1 = strtok(Input_Text," ");
        Input_Text += strlen(Param1)+1;
    }
    if(strlen(Input_Text) > 0) Param2 = strtok(Input_Text," ");
    else
    {
        printf("\n Incorrect username or password...");
        return;
    }
    if(debug)printf("\nUser:%s Pass:%s",Param1,Param2);
    Temp = User_Head->next;
    while(Temp)
    {
        if(Compare_Two_Strings(Temp->username , Param1))
        {
            printf("\n %s has been taken...Please try agian.",Param1);
            return;
        }
        Temp = Temp->next;
    }
    Temp = malloc(sizeof(user));
    Temp->username = Param1;
    Temp->password = Param2;
    post *Temp2 =  malloc(sizeof(post));
    Temp->posts = Temp2;
    Temp->posts->next = NULL;
    Temp->Post_Count = 0;
    Temp->Post_Index = 0;
    Temp->next = User_Head->next;
    User_Head->next = Temp;
    printf("\nUser:%s has been created successfully.",Param1);
    if(debug)
    {
        int i=1;
        Temp = User_Head->next;
        while(Temp)
        {
            printf("\n %d: User:%s  Pass:%s",i++,Temp->username,Temp->password);
            Temp = Temp->next;
        }
    }
}
void LogIN(void)
{
    user *Temp;
    char *Param1,*Param2;
    if (Current_User)
    {
        printf("\n Please logout first...");
        return;
    }
    if(strlen(Input_Text) > 0)
    {
        Param1 = strtok(Input_Text," ");
        Input_Text += strlen(Param1)+1;
    }
     if(strlen(Input_Text) > 0) Param2 = strtok(Input_Text," ");
    else
    {
        printf("\n Incorrect username or password...");
        return;
    }
    if(debug)printf("\nUser:%s Pass:%s",Param1,Param2);
    Temp = User_Head->next;
    while(Temp)
    {
        if(Compare_Two_Strings(Temp->username , Param1))
        {
            if(!Compare_Two_Strings(Temp->password,Param2))
            {
                printf("\n Incorrect password...");
                return;
            }
            else
            {
                printf("welcome back %s.",Param1);
                Current_User = Temp;
                return;
            }
        }
        Temp = Temp->next;
    }
    printf("%s does not exsit",Param1);
}
void LogOUT(void)
{
    if(Current_User)
    {
        printf("Goodbye %s.",Current_User->username);
        Current_User = NULL;
    }
}

char Compare_Two_Strings(char *First_World , char Second_World[])
{
    int a =1;
    for(int counter = 0 ; (Second_World[counter]) ; counter++)
        if(*(First_World +counter) != *(Second_World +counter))
            a=0;
    return a;
}

char Distiguish_command_Type(char *world)
{
    if (Compare_Two_Strings(world , "signup"))
    {
        Command_Type = Sign_UP;
        Input_Text += 7;  // chra 7 ta?  
    }   
    else if (Compare_Two_Strings(world , "login"))
    {
        Command_Type = LOG_IN;
        Input_Text += 6;
    }
    else if (Compare_Two_Strings(world , "logout"))
    {
        Command_Type = LOG_OUT;
        Input_Text += 7;
    }
    else if (Compare_Two_Strings(world , "post"))
    {
        Command_Type = POST;
        Input_Text += 5;
    }
    else if (Compare_Two_Strings(world , "like"))
    {
        Command_Type = LIKE;
        Input_Text += 5;
    }
    else if (Compare_Two_Strings(world , "delete"))
    {
        Command_Type = DELETE_POST;
        Input_Text += 7;
    }
    else if (Compare_Two_Strings(world , "info"))
    {
        Command_Type = INFO;
        Input_Text += 5;
    }
    else if (Compare_Two_Strings(world , "find_user"))
    {
        Command_Type = FIND_USER;
        Input_Text += 10;
    }
    else if(Compare_Two_Strings(world , "save"))
    {
        Command_Type = SAVE;
        Input_Text += 5;

    }
    else
        Command_Type = -1;
    return Command_Type;
}