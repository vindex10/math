//  (C) Copyright John Maddock 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/math/tools/formatting.hpp>
#include <complex>
#include <fstream>

void print(std::ostream& os)
{
   boost::math::tools::latex_printer printer(os);

   printer << "\\documentclass[10pt]{article}" << std::endl;
   printer << "\\usepackage{lingmacros}" << std::endl;
   printer << "\\usepackage{tree-dvips}" << std::endl;
   printer << "\\usepackage[a4paper, left = { 0.5in }]{ geometry }" << std::endl;
   printer << "\\begin{document}" << std::endl << std::endl;

   int ival = 0;
   printer << "\\textbf{Basic Integer Values}\n\n\\begin{tabular}{r r r}\nValue & Base & Result \\\\ \\hline \n";
   printer.stream() << ival << " & default & ";
   printer << ival << "\\\\\n";
   ival = -23;
   printer.stream() << ival << " & default & ";
   printer << ival << " \\\\\n";
   ival = 23;
   printer.stream() << std::dec << ival << " & hex & ";
   printer << std::hex << ival << "\\\\\n";
   printer.stream() << std::dec << ival << " & oct & ";
   printer << std::oct << ival << "\\\\\n\\end{tabular}\n\n";

   double fval = 3;
   printer << "\\textbf{Basic Float Values}\n\n\\begin{tabular}{r r r r}\nValue & Precision & Format & Result \\\\\n";
   printer.stream() << fval << " & default & default & ";
   printer << fval << " \\\\\n";
   fval = 3.14;
   printer.stream() << fval << " & default & default & ";
   printer << fval << " \\\\\n";
   fval = -1.2345678765e-24;
   printer.stream() << fval << " & default & default & ";
   printer << fval << " \\\\\n";
   printer.stream() << fval << " & 3 & scientific & ";
   printer << std::setprecision(3) << std::scientific << fval << " \\\\\n";
   printer.stream() << fval << " & 10 & scientific + latex\\_as\\_text & ";
   printer << std::setprecision(10) << boost::math::tools::latex_as_text << std::scientific << fval << " \\\\\n" << boost::math::tools::latex_as_equation;

   printer.stream() << fval << " & 3 & scientific + multiply\\_x & ";
   printer << std::setprecision(3) << std::scientific << boost::math::tools::multiply_x << fval << " \\\\\n";
   printer.stream() << fval << " & 10 & scientific + latex\\_as\\_text + multiply\\_x & ";
   printer << std::setprecision(10) << boost::math::tools::latex_as_text << boost::math::tools::multiply_x << std::scientific << fval << " \\\\\n" << boost::math::tools::latex_as_equation;
   printer.stream() << fval << " & 3 & scientific + multiply\\_dot & ";
   printer << std::setprecision(3) << std::scientific << boost::math::tools::multiply_dot << fval << " \\\\\n";
   printer.stream() << fval << " & 10 & scientific + latex\\_as\\_text + multiply\\_dot & ";
   printer << std::setprecision(10) << boost::math::tools::latex_as_text << boost::math::tools::multiply_dot << std::scientific << fval << " \\\\\n" 
      << boost::math::tools::latex_as_equation << boost::math::tools::multiply_times << std::defaultfloat;

   // Special Values:
   fval = 0;
   printer.stream() << fval << " & default & default & ";
   printer << fval << " \\\\\n";
   fval = -fval;
   printer.stream() << fval << " & default & default & ";
   printer << fval << " \\\\\n";
   fval = std::numeric_limits<double>::infinity();
   printer.stream() << fval << " & default & default & ";
   printer << fval << " \\\\\n";
   fval = -fval;
   printer.stream() << fval << " & default & default & ";
   printer << fval << " \\\\\n";
   fval = std::numeric_limits<double>::quiet_NaN();
   printer.stream() << fval << " & default & default & ";
   printer << fval << " \\\\\n";
   printer << boost::math::tools::latex_as_text;
   fval = 0;
   printer.stream() << fval << " & default & latex\\_as\\_text & ";
   printer << fval << " \\\\\n";
   fval = -fval;
   printer.stream() << fval << " & default & latex\\_as\\_text & ";
   printer << fval << " \\\\\n";
   fval = std::numeric_limits<double>::infinity();
   printer.stream() << fval << " & default & latex\\_as\\_text & ";
   printer << fval << " \\\\\n";
   fval = -fval;
   printer.stream() << fval << " & default & latex\\_as\\_text & ";
   printer << fval << " \\\\\n";
   fval = std::numeric_limits<double>::quiet_NaN();
   printer.stream() << fval << " & default & latex\\_as\\_text & ";
   printer << fval << " \\\\\n";
   printer << boost::math::tools::latex_as_equation;

   printer << "\\end{tabular}\n\n" << std::defaultfloat;

   std::complex<double> cval(3.25, 4.67);
   printer << "\\textbf{Basic Complex Values}\n\n\\begin{tabular}{r r r r}\nValue & Precision & Format & Result \\\\\n";
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   cval = 3.14;
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   cval = std::complex<double>(1.23, -1.2345678765e-24);
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   printer.stream() << cval << " & 3 & scientific & ";
   printer << std::scientific << std::setprecision(3) << cval << " \\\\\n";
   printer.stream() << cval << " & 12 & default + slanted\\_i & ";
   printer << boost::math::tools::slanted_i << std::defaultfloat << std::setprecision(12) << cval << " \\\\\n";
   printer.stream() << cval << " & 12 & default + upright\\_i & ";
   printer << boost::math::tools::upright_i << std::defaultfloat << std::setprecision(12) << cval << " \\\\\n";
   printer.stream() << cval << " & 12 & default + slanted\\_i + latex\\_as\\_text & ";
   printer << boost::math::tools::slanted_i << boost::math::tools::latex_as_text << std::defaultfloat << std::setprecision(12) << cval << " \\\\\n";
   printer.stream() << cval << " & 12 & default + upright\\_i + latex\\_as\\_text& ";
   printer << boost::math::tools::upright_i << std::defaultfloat << std::setprecision(12) << cval << " \\\\\n";
   printer << "\\end{tabular}\n\n" << std::defaultfloat << boost::math::tools::multiply_times;

   printer << "\\textbf{Complex Special Values}\n\n\\begin{tabular}{r r r r}\nValue & Precision & Format & Result \\\\\n";
   cval = std::complex<double>(0, 0);
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   printer.stream() << cval << " & default & show\\_zero\\_components & ";
   printer << boost::math::tools::show_zero_components  << cval << " \\\\\n" << boost::math::tools::hide_zero_components;
   cval = std::complex<double>(2.5, 0);
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   printer.stream() << cval << " & default & show\\_zero\\_components & ";
   printer << boost::math::tools::show_zero_components << cval << " \\\\\n" << boost::math::tools::hide_zero_components;
   cval = std::complex<double>(-2.5, 0);
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   printer.stream() << cval << " & default & show\\_zero\\_components & ";
   printer << boost::math::tools::show_zero_components << cval << " \\\\\n" << boost::math::tools::hide_zero_components;
   cval = std::complex<double>(0, 2.5);
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   printer.stream() << cval << " & default & show\\_zero\\_components & ";
   printer << boost::math::tools::show_zero_components << cval << " \\\\\n" << boost::math::tools::hide_zero_components;
   cval = std::complex<double>(0, -2.5);
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   printer.stream() << cval << " & default & show\\_zero\\_components & ";
   printer << boost::math::tools::show_zero_components << cval << " \\\\\n" << boost::math::tools::hide_zero_components;
   // Infinity:
   cval = std::complex<double>(std::numeric_limits<double>::infinity(), 2.5);
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   cval = std::complex<double>(2.5, std::numeric_limits<double>::infinity());
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   // NaN:
   cval = std::complex<double>(std::numeric_limits<double>::quiet_NaN(), 2.5);
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   cval = std::complex<double>(2.5, std::numeric_limits<double>::quiet_NaN());
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   cval = std::complex<double>(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::infinity());
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   cval = std::complex<double>(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN());
   printer.stream() << cval << " & default & default & ";
   printer << cval << " \\\\\n";
   printer << "\\end{tabular}\n\n" << std::defaultfloat << boost::math::tools::multiply_times;


   printer << "\\end{document}\n\n";
}

int main(int argc, const char* argv[])
{
   if (argc > 1)
   {
      std::ofstream ofs(argv[1]);
      print(ofs);
   }
   else
      print(std::cout);
   return 0;
}
