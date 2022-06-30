#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <stdlib.h>

using namespace std;

ifstream infile("input_Phase_1.txt");
ofstream outfile;

class OS
{
public:
    void load();
    OS()
    {
    }

private:
    char memory[100][4] = {'*', '*'}, IR[4], C, R[4];
    int blocks = 0, IC = 0, m = 0, data_counter, address, row_no, col_no, SI = 3;
    string next_to_amj = "abcd", data;
    
    void reset_memory();
    void start_execution();
    void execute_user_program();
    void go_to_end();
    void MOS();
    void show_memory()
    {
        cout << "Memory :\n";
        for (int i = 0; i < m; i++)
        {
            cout << i << ": ";
            for (int j = 0; j < 4; j++)
                cout << memory[i][j] << " ";
            cout << "\n";
        }
    }
};

void OS::load()
{
    int flag = 0;
    reset_memory();

    while (infile)
    {
        string file_content, sub_string, temp, trimmed_string;
        if (!getline(infile, file_content))
            break;
        temp = file_content.substr(0, 4);
        if (temp == "$END")
        {
            reset_memory();
            IC = m = data_counter = address = 0;
            outfile << "\n\n";
            continue;
        }
        else if (temp == "$AMJ")
        {
            flag = 0;
            while (getline(infile, next_to_amj))
            {
                while (next_to_amj != "")
                {
                    trimmed_string = next_to_amj.substr(0, 4);
                    if (!trimmed_string.find('H'))
                    {
                        flag = 1;
                        break;
                    }
                    next_to_amj.erase(0, 4);
                    memory[m][0] = trimmed_string[0];
                    memory[m][1] = trimmed_string[1];
                    memory[m][2] = trimmed_string[2];
                    memory[m][3] = trimmed_string[3];
                    m++;
                }
                if (flag == 1)
                    break;
            }
            cout << "code in memory \n";
            show_memory();
        }
        else if (temp == "$DTA")
        {
            start_execution();
        }
    }
}

void OS::reset_memory()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 4; j++)
            memory[i][j] = '*';
}

void OS::start_execution()
{
    IC = 0;
    execute_user_program();
}

void OS::execute_user_program()
{
    for (IC = 0; IC < m; IC++)
    {

        string temp, temp1, instruction;
        for (int j = 0; j < 4; j++)
        {
            IR[j] = memory[IC][j];
        }
        cout << "\n";
        temp = IR[0];
        temp1 = IR[1];
        instruction = temp + temp1;
        row_no = (IR[2] - '0') * 10 + (IR[3] - '0');

        cout << "Execution" << IC << ": ";
        cout << instruction << IR[2] << IR[3] << endl;
        if (instruction == "GD")
        {
            SI = 1;
            MOS();
        }
        else if (instruction == "PD")
        {
            SI = 2;
            MOS();
        }
        else if (instruction == "LR")
        {

            for (int i = 0; i < 4; i++)
                R[i] = memory[row_no][i];
        }
        else if (instruction == "SR")
        {
            for (int i = 0; i < 4; i++)
                memory[row_no][i] = R[i];
        }
        else if (instruction == "CR")
        {
            int flag = 0;
            for (int i = 0; i < 4; i++)
                if (memory[row_no][i] != R[i])
                    flag = 1;
            if (flag == 0)
                C = 'T';
            else
                C = 'F';
            flag = 0;
            cout << "C: " << C << endl;
        }
        else if (instruction == "BT")
        {
            cout << "C is " << C << endl;
            if (C == 'T')
                IC = ((IR[2] - 48) * 10) + (IR[3] - 48);
            C = 'F';
            cout << "Instruction counter is now " << IC << endl;
        }
    }
    cout << "Memory After Execution :\n";
    for (int i = 0; i < 100; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < 4; j++)
            cout << memory[i][j] << " ";
        cout << "\n";
    }
}

void OS::MOS()
{
    switch (SI)
    {
    case 1:
    {
        string temp;
        data = "";
        getline(infile, data);
        cout << "Data is " << data << endl;
        temp = data.substr(0, 4);
        if (temp == "$END" || temp == "")
        {
            cout << "Out Of Data \n";
            reset_memory();
            IC = m = data_counter = address = 0;
            outfile << "Out Of Data \n";
            outfile << "\n\n";
        }
        if (row_no > 100)
        {
            cout << "Memory is exceeded \n"
                 << endl;
            cout << "Row no " << row_no << endl;
            reset_memory();
            IC = m = data_counter = address = 0;
            outfile << "Memory is exceeded \n";
            outfile << "\n\n";
            go_to_end();
        }
        int counter = 0;
        cout << "Row No is " << row_no << endl;
        for (int i = row_no; counter < (data.length()); i++)
            for (int j = 0; j < 4 && counter < (data.length()); j++)
            {
                memory[i][j] = data[counter];
                counter += 1;
                if (counter > 40)
                    break;
            }
        break;
    }

    case 2:
    {
        string space = " ";
        int count = 0;
        char *buffer = new char[1];
        for (int row = row_no; count < 10; row++)
        {
            count++;
            for (int col = 0; col < 4; col++)
            {
                if (memory[row][col] != '*')
                    outfile << memory[row][col];
            }
        }
        outfile << "\n";
        break;
    }

    case 3:
        cout << "Halt Here";
    }
    SI = 0;
}

void OS::go_to_end()
{
    string temp, file_content;
    while (1)
    {
        if (!getline(infile, file_content))
            break;
        temp = file_content.substr(0, 4);
        if (temp == "$END")
            return;
    }
}

int main()
{
    OS myOS;
    outfile.open("output_phase_1.txt");
    myOS.load();
    infile.close();
    outfile.close();
}