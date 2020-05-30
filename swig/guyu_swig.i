/* -*- c++ -*- */

#define GUYU_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "guyu_swig_doc.i"

%{
#include "guyu/print_data_f.h"
#include "guyu/myCMA22.h"
#include "guyu/my_DQPSK_Demod.h"
#include "guyu/my_file_sink.h"
%}

%include "guyu/print_data_f.h"
GR_SWIG_BLOCK_MAGIC2(guyu, print_data_f);

%include "guyu/myCMA22.h"
GR_SWIG_BLOCK_MAGIC2(guyu, myCMA22);



%include "guyu/my_DQPSK_Demod.h"
GR_SWIG_BLOCK_MAGIC2(guyu, my_DQPSK_Demod);
%include "guyu/my_file_sink.h"
GR_SWIG_BLOCK_MAGIC2(guyu, my_file_sink);
