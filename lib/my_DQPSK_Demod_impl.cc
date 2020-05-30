/* -*- c++ -*- */
/* 
 * Copyright 2020 guyu.
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
#include "my_DQPSK_Demod_impl.h"
#include <volk/volk.h>
#include <gnuradio/math.h>

namespace gr {
  namespace guyu {

    my_DQPSK_Demod::sptr
    my_DQPSK_Demod::make()
    {
      return gnuradio::get_initial_sptr
        (new my_DQPSK_Demod_impl());
    }

    /*
     * The private constructor
     */
    my_DQPSK_Demod_impl::my_DQPSK_Demod_impl()
      : gr::sync_block("my_DQPSK_Demod",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      diff_angle = 0;
      last_angle = PI/4;
    }

    /*
     * Our virtual destructor.
     */
    my_DQPSK_Demod_impl::~my_DQPSK_Demod_impl()
    {
    }

    int
    my_DQPSK_Demod_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>
      for (int i = 0; i < noutput_items; i++){
	diff_angle = std::arg(in[i]) - last_angle;
	last_angle = std::arg(in[i]);
	
	while (diff_angle < 0)
	{
	  diff_angle = diff_angle + 2*PI;
	}
	
	if (diff_angle >= PI/4 && diff_angle < 3*PI/4)
	{
	  out[i] = 1;
	}
	else if (diff_angle >= 3*PI/4 && diff_angle < 5*PI/4)
	{
	  out[i] = 2;
	}
	else if (diff_angle >= 5*PI/4 && diff_angle < 7*PI/4)
	{
	  out[i] = 3;
	}
	else
	{
	  out[i] = 0;
	}
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace guyu */
} /* namespace gr */

