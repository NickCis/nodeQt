#!/usr/bin/env python

def set_options(ctx):
  ctx.tool_options('compiler_cxx')

def configure(ctx):
  ctx.check_tool('compiler_cxx')
  ctx.check_tool('node_addon')
  ctx.check_cfg(package='Qt3Support', uselib_store='Qt3Support', args='--cflags --libs')

def build(ctx):
  t = ctx.new_task_gen('cxx', 'shlib', 'node_addon', uselib = 'Qt3Support')
  t.cxxflags = ['-DQT_NO_DEBUG', '-DQT_GUI_LIB', '-DQT_CORE_LIB', '-DQT_SHARED']
  t.target = 'nodeQt'
  t.source = [
      'src/nodeQt.cpp',
      'src/pushButton.cpp',
      'src/Widget.cpp',
      'src/Application.cpp',
      #'src/Window.cpp',
      #Qt Things
      'src/QtAction.cpp'
      #,'src/QtWindow.cpp'
  ]
  t.uselib = ['Qt3Support']
