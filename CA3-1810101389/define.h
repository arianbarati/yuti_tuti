#define debug 0

#define Sign_UP 'u'
#define LOG_IN 'i'
#define LOG_OUT 'o'
#define POST 'p'
#define LIKE 'l'
#define DELETE_POST 'd'
#define INFO 'n'
#define FIND_USER 'f'
#define SAVE 's'

typedef struct post_properties post;
typedef struct user_properties user;

struct post_properties
{
    char* text ;
    int likes;
    int post_id;
    post* next;
};
struct user_properties
{
    char *username;
    char *password ;
    int Post_Count;
    int Post_Index;
    post *posts;
    user* next;
};

void Init(void);
void Get_Commad(void);
void Reply_Command(void);
void SignUP(void);
void LogIN(void);
void LogOUT(void);
char Compare_Two_Strings(char *First_World , char *Second_World);
char Distiguish_command_Type(char *world);

char Command_Type;
char *Input_Text;
user *User_Head,*Current_User;