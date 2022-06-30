#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;


//* Global variables
ifstream infile("input_Phase_2.txt");
ofstream outfile;
std::string::size_type sz; 

typedef struct PCB
{
    int TTL, TLL, JOB_ID;
} PCB;

class OS
{
public:
    void load();
    OS()
    {
        
    }

private:
    string next_to_amj = "cdss", data;
    int blocks = 0, IC = 0, m = 0, VA, data_counter, address, row_no, col_no, SI = 0, PTR, TTC, TLC, PI, TI, RA, flag_for_end;
    bool occupied[30] = {false};
    string instruction;
    PCB pcb;

    char memory[300][4] = {'*', '*'}, IR[4], C, R[4];
    void startexecution();
    void executeuserprogram();
    void MOS();
    void TERMINATE(int);
    int calculate_address();
    void go_to_end();
    void reset_memory();
    PCB init_PCB(string file_content);

    int ALLOCATE();
    void SIMULATION();

    void update_page_table(int);
    int ADDRESS_MAP(int VA1);
    void set_pt();
    bool isvalid(char num);
};

void OS::go_to_end()
{
    string temp, file_content, end_check;
    end_check = data.substr(0, 4);
    if (end_check != "$END")
    {
        while (1)
        {
            if (!getline(infile, file_content))
                break;                        
            temp = file_content.substr(0, 4); 
            if (temp == "$END")               
            {
                break;
            }
        }
    }
    flag_for_end = 1;
    reset_memory();
    return;
}

void OS::reset_memory()
{
    for (int i = 0; i < 300; i++)
        for (int j = 0; j < 4; j++)
            memory[i][j] = '*';
    occupied[0] = true;
    for (int i = 1; i < 30; i++)
        occupied[i] = false;
    IC = 0;
    PI = 0;
    TI = 0;
    TTC = 0;
    TLC = 0;
}

PCB OS::init_PCB(string file_content)
{
    string
        job_id = file_content.substr(4, 4);
    int
        job_id1 = std::stoi(job_id, &sz);
    pcb.JOB_ID = job_id1;
    string
        TTL = file_content.substr(8, 4);
    int
        TTL1 = std::stoi(TTL, &sz);
    pcb.TTL = TTL1;
    string
        TLL = file_content.substr(12, 4);
    int
        TLL1 = std::stoi(TLL, &sz);
    pcb.TLL = TLL1;
    return pcb;
}

int OS::ALLOCATE()
{
    int page_no;
    while (1)
    {
        page_no = rand() % 30;
        if (!occupied[page_no])
        {
            occupied[page_no] = true;
            break;
        }
    }
    return page_no;
}

int OS::ADDRESS_MAP(int VA1)
{
    int loc, fno, RA, flag1 = 1;
    if (VA1 >= 100)
    {
        PI = 2; //* Operand Error
        MOS();
        return 0;
    }
    loc = PTR + (VA1 / 10);
    if (memory[loc][0] == '0')
    {
        PI = 3; //* Page Fault Error
        MOS();
        if (flag_for_end)
            return -1;
    }
    fno = (memory[loc][2] - '0') * 10 + (memory[loc][3] - '0');
    RA = (fno * 10) + (VA1 % 10);
    return RA;
}

void OS::set_pt()
{
    int counter = PTR;
    while (counter < (PTR + 9))
    {
        for (int i = 0; i < 4; i++)
            memory[counter][i] = '0';
        counter++;
    }
}

void OS::update_page_table(int frame_no)
{
    for (int i = PTR; i < (PTR + 10); i++)
    {
        if (memory[i][0] == '0')
        {
            memory[i][0] = '1';
            int dec = (frame_no / 10);
            int unit = (frame_no % 10);
            memory[i][2] = (dec + '0');
            memory[i][3] = (unit + '0');
            break;
        }
    }
}

void OS::load()
{
    int flag = 0;
    reset_memory();
    while (infile)
    {
        int frame_no, fm;
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
            //break;
        }
        else if (temp == "$AMJ") 
        {
            flag_for_end = 0;
            PCB pcb_obj = init_PCB(file_content);

            cout << "Execution log for JobID : " << pcb.JOB_ID << endl;
            cout << "TTL: " << pcb.TTL << "\nTLL: " << pcb.TLL << endl
                 << endl;
            PTR = ALLOCATE(); 
            PTR *= 10;
            set_pt();
            flag = 0;
            while (getline(infile, next_to_amj))
            {
                frame_no = ALLOCATE();
                update_page_table(frame_no);
                frame_no *= 10;
                fm = frame_no;
                while (next_to_amj != "")
                {
                    trimmed_string = next_to_amj.substr(0, 4);
                    if (!trimmed_string.find('H'))
                    {
                        memory[frame_no][0] = 'H';
                        flag = 1;
                        break;
                    }
                    next_to_amj.erase(0, 4);
                    memory[frame_no][0] = trimmed_string[0];
                    memory[frame_no][1] = trimmed_string[1]; 
                    memory[frame_no][2] = trimmed_string[2];
                    memory[frame_no][3] = trimmed_string[3];
                    frame_no++;
                }
                if (flag == 1) 
                    break;
            }
        }
        else if (temp == "$DTA")
        {
            startexecution();
        }
    }
}

void OS::startexecution()
{
    IC = 0;
    executeuserprogram();
}

void OS::executeuserprogram()
{
    int address, row;
    string end = "H";
    while (1)
    {
        SI = 0;
        RA = ADDRESS_MAP(IC);
        IC++;
        string temp, temp1;
        for (int j = 0; j < 4; j++)
            IR[j] = memory[RA][j];
        temp = IR[0];
        temp1 = IR[1];
        instruction = temp + temp1;
        if (instruction[0] == 'H' && instruction[1] == '*')
        {
            TTC++;
            SI = 3; 
            MOS();
            break;
        }
        VA = calculate_address();
        if (flag_for_end)
        {
            flag_for_end = 0;
            break;
        }
        RA = ADDRESS_MAP(VA);
        if (instruction == "GD")
        {
            cout << "Get data from RA: " << RA << endl;
            SI = 1; 
            MOS();
        }
        else if (instruction == "PD")
        {
            SI = 2; 
            cout << "Data printed to output file at RA: " << RA << endl;
            MOS();
        }
        else if (instruction == "LR")
        {
            if (PI == 3)
                TERMINATE(6);
            for (int i = 0; i < 4; i++)
                R[i] = memory[RA][i];
            cout << "Loaded general register with RA : " << RA << endl;
        }
        else if (instruction == "SR")
        {
            PI = 0;
            for (int i = 0; i < 4; i++)
                memory[RA][i] = R[i];
            cout << "Content of general register stored at RA : " << RA << endl;
        }
        else if (instruction == "CR")
        {
            int flag = 0;
            for (int i = 0; i < 4; i++)
                if (memory[RA][i] != R[i])
                    flag = 1;
            if (flag == 0)
                C = 'T';
            else
                C = 'F';
            flag = 0;
            cout << "C register has been set to: " << C << endl;
        }
        else if (instruction == "BT")
        {
            if (C == 'T')
                IC = ((IR[2] - 48) * 10) + (IR[3] - 48);
            C = 'F';
            cout << "IC register has been set to: " << IC << endl;
        }
        else if (instruction == "H")
        {
            SI = 3;
            MOS();
        }
        else
        {
            PI = 1; 
        }
        if (flag_for_end)
        {
            flag_for_end = 0;
            break;
        }
        SIMULATION();
        if (PI != 0 || TI != 0)
            MOS();
        if (flag_for_end)
        {
            flag_for_end = 0;
            break;
        }
        if (instruction == "GD" || instruction == "SR")
            TTC += 2;
        else
            TTC++;
    }
    reset_memory();
}

void OS::MOS()
{
    int row_no1;
    //* If not a timer interrupt but system interrupt
    if (TI == 0)
    {
        switch (SI)
        {
        case 1: 
        {
            string temp;
            data = "";
            PI = 0;
            getline(infile, data);
            temp = data.substr(0, 4);
            if (temp == "$END" || temp == "")
            {
                //* Out of data Error
                TERMINATE(1);
            }
            int counter = 0;
            for (int i = RA; counter < (data.length()); i++)
                for (int j = 0; j < 4 && counter < (data.length()); j++)
                {
                    memory[i][j] = data[counter];
                    counter += 1;
                }
            break;
        }
        case 2: 
        {
            TLC++;
            if (TLC > pcb.TLL)
            {
                //* Line limit exceeded error
                TERMINATE(2);
                return;
            }
            if (PI == 3)
            {
                //* Page fault error
                TERMINATE(6);
                return;
            }
            int row;
            string space = " ";
            int count = 0;
            for (int row = RA; count < 10; row++)
            {
                count++;
                for (int col = 0; col < 4; col++)
                {
                    if (memory[row][col] != '*')
                    {
                        outfile << memory[row][col];
                    }
                }
            }
            outfile << "\n";
            break;
        }
        case 3:
        {
            TERMINATE(0);
            return;
        }
        }
    }

    //* incase of a timer interrupt and system interrupt
    else if (TI == 2)
    {

        switch (SI)
        {
        case 1: 
        {
            TERMINATE(3);
            break;
        }
        case 2:
        {
            TERMINATE(3);
            break;
        }
        case 3: 
        {
            TERMINATE(0);
            break;
        }
        }
    }

    //*if not a timer interrupt but a program interrupt
    if (TI == 0)
    {
        switch (PI)
        {
        case 1: 
            TERMINATE(4);
            break;
        case 2: 
            TERMINATE(5);
            break;
        case 3:
            //* Incase of PAGE FAULT
            if (instruction == "GD" || instruction == "SR")
            {
                int allocator = ALLOCATE();
                address = PTR + VA / 10;
                memory[address][0] = 0;
                memory[address][2] = ((allocator / 10) + '0');
                memory[address][3] = ((allocator % 10) + '0');
                allocator *= 10;
                RA = allocator;
                flag_for_end = 0;
                cout << "Valid page fault at IC: " << IC << endl;
            }
            else
            {
                TERMINATE(6); 
                cout << "Invalid page fault at IC: " << IC << endl;
            }
            break;
        }
    }

    //*Timer and Program error combine are handled here
    else if (TI == 2)
    {
        switch (PI)
        {
        case 1: 
            TERMINATE(7);
            break;
        case 2: 
            TERMINATE(8);
            break;
        case 3: 
            TERMINATE(3);
            break;
        default:
            TERMINATE(3);
            break;
        }
    }
    SI = 0;
}

int OS::calculate_address()
{
    if (isvalid(IR[2]) && isvalid(IR[3]))
        VA = (IR[2] - '0') * 10 + (IR[3] - '0');
    else
    {
        PI = 2; 
        SIMULATION();
        MOS();
        return 0;
    }
    return VA;
}

void OS::TERMINATE(int ERR_CODE)
{
    switch (ERR_CODE)
    {
    case 0:
        outfile << "Error Message : NO ERROR\n";
        break;
    case 1:
        outfile << "Error Message : OUT OF DATA\n";
        break;
    case 2:
        outfile << "Error Message : LINE LIMIT EXCEEDED\n";
        break;
    case 3:
        outfile << "Error Message : TIME LIMIT EXCEEDED\n";
        break;
    case 4:
        outfile << "Error Message : OPERATION CODE ERROR\n";
        break;
    case 5:
        outfile << "Error Message : OPERAND ERROR\n";
        break;
    case 6:
        outfile << "Error Message : INVALID PAGE FAULT\n";
        break;
    case 7:
        outfile << "Error Message : TIME LIMIT EXCEEDED\ncpu_em : OPERATION CODE ERROR\n";
        break;
    case 8:
        outfile << "Error Message : TIME LIMIT EXCEEDED\ncpu_em : OPERAND ERROR\n";
        break;
    }
    cout << "End of Execution of JobID: " << pcb.JOB_ID << "\n\n\n";
    outfile << "mos_execute : Job Details \n"
            << "JID\t"
            << "IC\t"
            << "IR\t"
            << "TTL\t"
            << "TLL\t"
            << "TTC\t"
            << "TLC\n";
    outfile << pcb.JOB_ID << "\t" << IC << "\t" << IR[0] << IR[1] << IR[2] << IR[3] << "\t" << pcb.TTL << "\t" << pcb.TLL << "\t" << TTC << "\t" << TLC << "\n\n\n";
    go_to_end();
}

void OS::SIMULATION()
{
    if (TTC >= pcb.TTL)
    {
        TI = 2;
        MOS();
    }
}

//*Helper functions
bool OS::isvalid(char num)
{
    if (num >= '0' && num <= '9')
        return true;
    return false;
}

int main()
{
    OS myos;
    outfile.open("output_phase_2.txt");
    myos.load();
    infile.close();
    outfile.close();
}
