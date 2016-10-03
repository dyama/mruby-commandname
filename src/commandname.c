#include <mruby.h>
#include <mruby/string.h>
#include <stdio.h>
#include <stdlib.h>

#define SELFPATH_LIMIT 256

#include <windows.h>

static mrb_value mrb_command_name(mrb_state* mrb, mrb_value self)
{
  char path[SELFPATH_LIMIT] = {0};
  if (GetModuleFileName(NULL, path, SELFPATH_LIMIT - 1) == 0) {
    return mrb_nil_value();
  }
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

