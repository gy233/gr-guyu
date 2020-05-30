/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "print_data_f_impl.h"

#include<fstream>

namespace gr {
  namespace guyu {

    print_data_f::sptr
    print_data_f::make()
    {
      return gnuradio::get_initial_sptr
        (new print_data_f_impl());
    }

    /*
     * The private constructor
     */
    print_data_f_impl::print_data_f_impl()
      : gr::sync_block("print_data_f",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    print_data_f_impl::~print_data_f_impl()
    {
    }

    int
    print_data_f_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
			std::ofstream openfile("/home/guyu/print_data_f.txt");
			for(int i=0;i<noutput_items;i++)
			{
				//std::cout<<in[i]<<std::endl;
				openfile<<in[i]<<std::endl;
				out[i]=in[i];
			}
			openfile.close();

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace guyu */
} /* namespace gr */

