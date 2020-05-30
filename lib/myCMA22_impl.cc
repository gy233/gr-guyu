/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
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
#include "myCMA22_impl.h"

#include<fstream>
#include <ctime>

namespace gr {
  namespace guyu {

    myCMA22::sptr
    myCMA22::make(int num_taps, float modulus, float mu, int sps, int iter, bool print_flag)
    {
      return gnuradio::get_initial_sptr
        (new myCMA22_impl(num_taps, modulus, mu, sps, iter, print_flag));
    }

    /*
     * The private constructor
     */
    myCMA22_impl::myCMA22_impl(int num_taps, float modulus, float mu, int sps, int iter, bool print_flag)
      : gr::sync_decimator("myCMA22",
              gr::io_signature::make(2, 2, sizeof(gr_complex)),
              gr::io_signature::make(2, 2, sizeof(gr_complex)), sps),
	d_new_taps(num_taps, gr_complex(0,0)),
        d_new_taps1(num_taps, gr_complex(0,0)),
        d_print_flag(print_flag),
	d_updated(false), d_error(gr_complex(0,0))
    {
      std::time_t now = std::time(0);
      char* dt = std::ctime(&now);
      if(d_print_flag)
      {
        std::ofstream openfile;
        openfile.open("/home/guyu/my_gnuradio_projects/cma/myCMA22_cc.txt", std::fstream::out);
        openfile<<dt<<std::endl;
        openfile.close();
        openfile.open("/home/guyu/my_gnuradio_projects/cma/myCMA22_cc1.txt", std::fstream::out);
        openfile<<dt<<std::endl;
        openfile.close();
      }
      set_modulus(modulus);
      set_gain(mu);
      set_iteration(iter);
      if(num_taps > 0 && num_taps%2==0 && num_taps%4==2){
	d_new_taps[(num_taps-2)/4] = 1.0;
        d_new_taps1[(3*num_taps-2)/4] = 1.0;
      }
      else{
        throw std::out_of_range("myCMA22::num_taps: num_taps value must be (2*N+1)*2");
      }
      d_filter_1 = new gr::filter::kernel::fir_filter_ccc(1,d_new_taps);
      d_filter_2 = new gr::filter::kernel::fir_filter_ccc(1,d_new_taps1);
      set_history(num_taps);
    }

    /*
     * Our virtual destructor.
     */
    myCMA22_impl::~myCMA22_impl()
    {
    }

    void
    myCMA22_impl::set_taps(const std::vector<gr_complex> &taps)
    {
      d_filter_1->set_taps(d_new_taps);
      d_filter_2->set_taps(d_new_taps1);
      d_updated = true;
    }

    std::vector<gr_complex>
    myCMA22_impl::taps() const
    {
      return d_new_taps;
    }

    gr_complex
    myCMA22_impl::error(const gr_complex &out)
    { 
      gr_complex error = out*(norm(out) - d_modulus);
      float re = gr::clip(error.real(), 1.0);  //ensure error.real() belong to [-1,1], gr::clip is defined in math.h
      float im = gr::clip(error.imag(), 1.0);  //ensure error.imag() belong to [-1,1]
      return gr_complex(re, im);
    }

    void
    myCMA22_impl::update_tap(gr_complex &tap, const gr_complex &in)
    {
      tap -= d_mu*conj(in)*d_error;
    }

    int
    myCMA22_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in1 = (const gr_complex *) input_items[0];
      const gr_complex *in2 = (const gr_complex *) input_items[1];
      gr_complex *out1 = (gr_complex *) output_items[0];
      gr_complex *out2 = (gr_complex *) output_items[1];
      gr_complex in[d_new_taps.size()];
      gr_complex out1_temp;
      gr_complex out2_temp;
      std::ofstream openfile;
      // Do <+signal processing+>

      if(d_updated) {
        set_history(d_new_taps.size());
        set_history(d_new_taps1.size());
	d_updated = false;
	return 0;     // history requirements may have changed.
      }

      int j = 0;
      size_t k;
      size_t l = d_new_taps.size();
      size_t l1 = d_new_taps1.size();
      for(int i = 0; i < noutput_items; i++) {

        // combine in1 and in2
        for(int ii = 0; ii < l/2; ii++) {
          in[ii]=in1[ii+j];
          in[l/2+ii]=in2[ii+j];
        }

          
        if(d_print_flag)
        {
          openfile.open("/home/guyu/my_gnuradio_projects/cma/myCMA22_cc.txt", std::fstream::out | std::fstream::app);
          openfile<<"in"<<std::endl;
          for(int ii = 0; ii < l; ii++) {
            openfile<<in[ii]<<std::endl;
          }
          openfile.close();
        }
      
        for(int times=0; times<d_iter; times++)
        {
          // out1
          out1_temp = d_filter_1->filter(&in[0]);

          if(d_print_flag)
          {
            openfile.open("/home/guyu/my_gnuradio_projects/cma/myCMA22_cc.txt", std::fstream::out | std::fstream::app);
            openfile<<"out1"<<std::endl;
            openfile<<out1_temp<<std::endl;
            openfile.close();
          }

          // Adjust taps
          d_error = error(out1_temp);
          
          if(d_print_flag)
          {
            openfile.open("/home/guyu/my_gnuradio_projects/cma/myCMA22_cc.txt", std::fstream::out | std::fstream::app);
            openfile<<"d_error"<<std::endl;
            openfile<<print_error()<<std::endl;
            openfile.close();
          }
          
	  for(k = 0; k < l; k++) {
	    // Update tap locally from error.
	    update_tap(d_new_taps[k], in[k]);

	    // Update aligned taps in filter object.
	    d_filter_1->update_tap(d_new_taps[k], k);
	  }

          if(d_print_flag)
          {
            openfile.open("/home/guyu/my_gnuradio_projects/cma/myCMA22_cc.txt", std::fstream::out | std::fstream::app);
            openfile<<"d_new_taps"<<std::endl;
            for(k = 0; k < l; k++) {
	      openfile<<d_new_taps[k]<<std::endl;
	    }
	    openfile<<std::endl;
            openfile.close();
          }

          // out2
          out2_temp = d_filter_2->filter(&in[0]);

          if(d_print_flag)
          {
            openfile.open("/home/guyu/my_gnuradio_projects/cma/myCMA22_cc1.txt", std::fstream::out | std::fstream::app);
            openfile<<"out2"<<std::endl;
            openfile<<out2_temp<<std::endl;
            openfile.close();
          }

          // Adjust taps
	  d_error = error(out2_temp);
	  for(k = 0; k < l1; k++) {
	    // Update tap locally from error.
	    update_tap(d_new_taps1[k], in[k]);

	    // Update aligned taps in filter object.
	    d_filter_2->update_tap(d_new_taps1[k], k);
	  }

          if(d_print_flag)
          {
            openfile.open("/home/guyu/my_gnuradio_projects/cma/myCMA22_cc1.txt", std::fstream::out | std::fstream::app);
            openfile<<"d_new_taps1"<<std::endl;
	    for(k = 0; k < l1; k++) {
	      openfile<<d_new_taps1[k]<<std::endl;
	    }
            openfile<<std::endl;
            openfile.close();
          }
        }
        out1[i] = out1_temp;
        out2[i] = out2_temp;
        j += decimation();
        
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace guyu */
} /* namespace gr */

