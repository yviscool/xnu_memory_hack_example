#include "vm_mem.hpp"

#include <iostream>
#include <memory>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
  const int offset = 0x28;
  int num_ptr = 8;
  int *pointer_path;

  pointer_path = (int *)malloc(num_ptr * sizeof(int));

  pointer_path[0] = 0x0735D998;
  pointer_path[1] = 0x10;
  pointer_path[2] = 0x1C8;
  pointer_path[3] = 0x20;
  pointer_path[4] = 0x358;
  pointer_path[5] = 0x18;
  pointer_path[6] = 0x78;
  pointer_path[7] = 0xD70;

  // if(argc < 2)
  // {
  //   cout << "Usage : ./mem <process name>" << endl;
  //   exit(-1);
  // }
  // if(getuid() && geteuid())
  // {
  //   cout << "permission denied, please root." << endl;
  //   exit(-1); //
  // }

  // cout << "process : " << argv[1] << endl;
  Process *process = new Process();
  // kern_return_t kret = process->Open(argv[1]);
  kern_return_t kret = process->Open("minecraftpe");

  pid_t pid = process->get_pid();
  cout << "pid : " << pid << endl;

  if (pid != -1)
  {
    if (kret != KERN_SUCCESS)
    {
      cout << "open error, please check root." << endl;
    }
    else
    {
      cout << "opened process." << endl;
    }
  }
  else
  {
    cout << "process not found." << endl;
    exit(-1);
  }

  uint64_t base = process->get_base_address();
  cout << "base address : 0x" << hex << base << endl;

  // char buffer[11] = {0};

  uint64_t magic = process->Read<uint64_t>(base + pointer_path[0]);
  cout << "num_ptr " << (void *)magic << endl;

  uint64_t  cur_ptr = 0;
  for (int i = 1; i < num_ptr - 1; i++)
  {
    cur_ptr = magic + pointer_path[i];
    magic = process->Read<uint64_t>(cur_ptr);
    cout << "num_ptr " << (void *)magic << " " << dec <<  pointer_path[i] << endl;
  }

  // uint32_t magic = process->Read<uint32_t>(0x7F9B3642C1A0);
  // cout << "magic 0x" << dec << magic << endl;
  magic += pointer_path[num_ptr - 1];

  process->Write<uint32_t>(magic, 8);

  // char value[11] = "__PUSH0EBP";
  // uint64_t addr = base + offset;

  // cout << "read/write to 0x" << hex << base << endl;
  // uint32_t magic = process->Read<uint32_t>(base);
  // uint32_t magic_value = 0xdeadbeef;
  // cout << "magic 0x" << hex << magic << endl;
  // cout << "write 0x" << magic_value << endl;
  // process->Write<uint32_t>(base, magic_value);
  // magic = process->Read<uint32_t>(base);
  // cout << "magic 0x" << hex << magic << endl;

  // cout << "read/write to 0x" << hex << addr << endl;
  // process->Read(addr, buffer, sizeof(buffer));
  // cout << "read " << buffer << endl;

  // process->Write(addr, value, sizeof(value));
  // cout << "write \"" << value << "\"" << endl;
  // memset(buffer, 0, sizeof(buffer));
  // process->Read( addr, buffer, sizeof(buffer));
  // cout << "read " << buffer << endl;

  return 0;
}
