#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <signal.h>
#include<iostream>
using namespace std;

void PrintDirectory()
{
    char currentdirectory[1024];
    getcwd(currentdirectory, sizeof(currentdirectory));
    cout << currentdirectory << endl;
}
int number_of_space(string line)
{
    int counter =0;
    for(int i=0; i<line.length(); i++)
    {
        if(line[i]==' ')
            counter++;
    }
    return counter;
}
void failure(string line)
{
    if(line=="exit" || line=="EXIT")
    {
        exit(0);
    }
}
void first_case(string input)
{
    char char_array_first[input.length()+1];
    string command_name = input;
    strcpy(char_array_first,input.c_str());
    char* line[2];
    line[0]= char_array_first;
    line[1]=NULL;
    pid_t fork_id = fork();
    if (fork_id == 0)
    {

        execvp(char_array_first,line);
        if(execvp(char_array_first,line) == -1)
        {
            cout<<"Invalid Input Command.."<<endl;
        }
    }
    else
    {
        wait(NULL);
    }
}
void second_case(string input,bool contain_and)
{
    char char_array_second[input.length()+1];
    char char_array_first[input.length()+1];
    string command_name = input.substr(0,input.find(' '));
    string arrgument = input.substr(input.find(' ')+1,input.length()-1);
    strcpy(char_array_first,command_name.c_str());
    char* line[3];
    line[0]= char_array_first;
    strcpy(char_array_second,arrgument.c_str());
    line[1]=char_array_second;
    line[2]=NULL;
    pid_t fork_id = fork();
    if (fork_id == 0)
    {
        execvp(char_array_first,line);
        if(execvp(char_array_first,line) == -1)
        {
            cout<<"Invalid Input Command.."<<endl;
        }
    }
    else
    {
        if(!contain_and)
        {
            wait(NULL);
        }
        else
        {

        }
    }
}
void third_case(string input)
{
    char char_array_first[input.length()+1];
    char char_array_second[input.length()+1];
    string command_name = input.substr(0,input.find(' '));
    input = input.substr(input.find(' ')+1,input.length()-1);
    string arrgument = input.substr(0,input.find(' '));
    string last_char = input.substr(input.find(' ')+1,input.length()-1);
    char* line[4];
    strcpy(char_array_first,command_name.c_str());
    line[0]=char_array_first;
    strcpy(char_array_second,arrgument.c_str());
    line[1]=char_array_second;
    strcpy(char_array_second,last_char.c_str());
    line[2]=char_array_second;
    line[3]=NULL;

    pid_t fork_id = fork();
    if (fork_id == 0)
    {
        execvp(char_array_first,line);
        if(execvp(char_array_first,line) == -1)
        {
            cout<<"Invalid Input Command.."<<endl;
        }
    }
    else
    {

    }
}
void fourth_case(string input)
{
    char char_array_first[input.length()+1];
    char char_array_second[input.length()+1];
    string command_name = input.substr(0,input.find(' '));
    input = input.substr(input.find(' ')+1,input.length()-1);
    string arrgument1 = input.substr(0,input.find(' '));
    string arrgument2 = input.substr(input.find(' ')+1,input.length()-1);

    char* line[4];
    strcpy(char_array_first,command_name.c_str());
    line[0]=char_array_first;
    strcpy(char_array_second,arrgument1.c_str());
    line[1]=char_array_second;
    strcpy(char_array_second,arrgument2.c_str());
    line[2]=char_array_second;
    line[3]=NULL;

    pid_t fork_id = fork();
    if (fork_id == 0)
    {
        execvp(char_array_first,line);
        if(execvp(char_array_first,line) == -1)
        {
            cout<<"Invalid Input Command.."<<endl;
        }
    }
    else
    {
        wait(NULL);
    }
}
bool have_and(string input)
{
    if(input.find('&') > 0 && input.find('&') < input.length())
    {
        return true;
    }
    return false;
}
bool have_space(string input)
{
    if(input.find(' ') > 0 && input.find(' ') < input.length())
    {
        return true;
    }
    return false;

}
bool check_cd(string input)
{
    bool first_check;
    if(number_of_space(input)== 1)
    {
        first_check = true;
    }
    if(first_check && input.substr(0,input.find(' ')) == "cd")
    {
        return true;
    }
    return false;
}
void cd_case(string input)
{
    char char_array_first[input.length()+1];
    string command_name = input.substr(0,input.find(' '));
    string arrgument = input.substr(input.find(' ')+1,input.length()-1);
    strcpy(char_array_first,arrgument.c_str());
    chdir(char_array_first);
}
void terminate_modify(int signal)
{
    FILE * TFile;
    TFile = fopen ("terminator.txt","a+");
    fputs ("Child process was terminated\n",TFile);
    fclose (TFile);

    return ;
}
bool last_and(string input)
{
    if(input[input.length()-1]=='&')
    {
        return true;
    }
    return false;
}
int main()
{
    string input;
    signal(SIGCHLD, terminate_modify);
    while(1)
    {
        PrintDirectory();
        getline(cin,input);
        failure(input);
        if(input=="")
        {
            continue;
        }
        else
        {
            bool is_cd = check_cd(input);
            char char_array_first[input.length()+1];
            if(is_cd == true)
            {
                cd_case(input);
                continue;
            }
            bool contain_and=have_and(input);
            bool conatin_space=have_space(input);
            if(!conatin_space)
            {
                first_case(input);
            }
            else if(number_of_space(input)==1)
            {
                second_case(input,contain_and);
            }
            else if(number_of_space(input)==2 && last_and(input)==true)
            {
                third_case(input);
            }
            else if(number_of_space(input)==2 && last_and(input)==false)
            {
                fourth_case(input);
            }
            else
            {
                cout<<"invalid Input"<<endl;
            }
        }
    }
    return 0;
}
