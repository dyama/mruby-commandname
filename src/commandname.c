#include <mruby.h>
#include <mruby/string.h>
#include <stdio.h>
#include <stdlib.h>

#define SELFPATH_LIMIT 4096

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

static mrb_value mrb_command_name(mrb_state* mrb, mrb_value self)
{
  char path[SELFPATH_LIMIT] = {0};
#ifdef _WIN32
  if (GetModuleFileName(NULL, path, SELFPATH_LIMIT - 1) == 0) {
    return mrb_nil_value();
  }
#else
  if (readlink("/proc/self/exe", path, sizeof(path)) == -1) {
    return mrb_nil_value();
  }
#endif
  return mrb_str_new_cstr(mrb, path);
}

void mrb_mruby_commandname_gem_init(mrb_state* mrb)
{
  mrb_define_class_method(mrb, mrb->kernel_module, "command_name", mrb_command_name, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb->kernel_module, "command_name", mrb_command_name, MRB_ARGS_NONE());
}

void mrb_mruby_commandname_gem_final(mrb_state* mrb)
{

}

