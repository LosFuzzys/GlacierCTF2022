#include <verilated.h>
#include "VStackmachine.h"
#include <unistd.h>

#define INSTRUCTION_LIMIT 85
#define TIME_LIMIT 5

VStackmachine* machine;
uint64_t main_time = 0;       // Current simulation time
// This is a 64-bit integer to reduce wrap over issues and
// allow modulus.  This is in units of the timeprecision
// used in Verilog (or from --timescale-override)

double sc_time_stamp() {        // Called by $time in Verilog
    return main_time;           // converts to double, to match
                                // what SystemC does
}
int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);
    
    machine = new VStackmachine();
    machine->rst = 1;
    machine->in = 0;
    machine->clk = 0;
    int instruction_counter = 0;

    assert(argc == 2);
    uint64_t wanted_prime = atoi(argv[1]);
    wanted_prime = strtoul(argv[1], 0, 10);

    printf("Welcome to the magic stack machine!\n"
           "Your task is to reach the magic number with our very limited instruction set.\n"
           "You must reach this goal using less than %d instructions.\n"
           "Please provide your instructions as hex string.\n"
           "You have %d seconds.\n"
           "Good luck.\n\n"
           "Magic Number: %zd\n"
           "Instruction input: ", INSTRUCTION_LIMIT, TIME_LIMIT, wanted_prime);
    alarm(TIME_LIMIT);
    while(!Verilated::gotFinish())
    {
        
        if (main_time > 10) {
            machine->rst = 0;   // Deassert reset
        }
        if ((main_time % 10) == 1) {
            machine->clk = 1;       // Toggle clock
        }
        if ((main_time % 10) == 6) {
            machine->clk = 0;
        }
        if(main_time > 10 && main_time % 10 == 8)
        {
            if(instruction_counter++ >= INSTRUCTION_LIMIT)
            {
                printf("Instruction limit reached\n");
                exit(-1);
            }
            char input = getchar();
            if(input != '\n' && input != '\0')
            {
                int ret = hex2int(input);
                
                if(ret == -1)
                {
                    printf("Invalid input\n");
                    exit(-1);
                }
                machine->in = ret;
                input++;
            }
            else
            {
                printf("End of instruction input, exiting...");
                exit(0);
            }
                

        }
        machine->eval();
        if(machine->err)
        {
            printf("The Stackmachine reported error code %d, exiting...\n", machine->out);
            exit(-1);
        }
        if(machine->out)
        {
            printf("\nDONE\n");
            printf("OUTPUT: %zd\n", (uint64_t)machine->out);
            printf("TARGET: %zd\n", (uint64_t)wanted_prime);
            if((uint64_t)machine->out == (uint64_t)wanted_prime)
            {
                printf("Good job! Here's the flag:\n");
                FILE* flag = fopen("/flag.txt", "r");
                char c;
                while((c = fgetc(flag)) != EOF)
                {
                    putchar(c);
                }
                exit(0);
            }
            printf("Wrong output, better luck next time!\n");
            
            exit(-1);
        }
        main_time++;            // Time passes...

    }


}