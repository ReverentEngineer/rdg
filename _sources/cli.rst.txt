Command Line Interface
=======================

RDG provides a command line interface for generating data without having
to interface programmatically. 

Usage
---------------
The following is the usage information:

.. code-block:: bash

   usage: rdg [options] [expression output_directory]

   options:
      --version   Print version and exit
      --help      Print usage information and exit


Description
---------------
When provided with an *expression* and an *output_directory*, **rdg** will
write *n* files into the direct named "1" through "*n*" where *n* is the number
of permutations that exists for the *expression*.

When provided with only an *expression*, **rdg** will write the generated
data to *stdout* using the protocol described below.

When provided with no arguments, **rdg** will read from line delineated
expressions from *stdin* and write the generated data to *stdout* using
the protocol described in the next section.

Protocol
--------------
In order to allow users to make uses of pipes, **rdg** implements a basic
protocol for permutations written to *stdout*. The protocol is described in
`ASN.1`_ below and encoded with the `Basic Encoding Rules`_:

.. code-block::

   Permutations ::= SEQUENCE {
       Permutation OCTET STRING;
   }

.. _ASN.1: https://en.wikipedia.org/wiki/ASN.1
.. _Basic Encoding Rules: https://en.wikipedia.org/wiki/X.690#BER_encoding

Examples
---------------

To generate files based on a regular expression in a directory:

.. code-block:: bash

   rdg "my(expression|statement)[123]" ./myoutputdir

To stream an expression to stdout:

.. code-block:: bash

   rdg "my(expression|statement)[123]" | data_handling_program

To stream from stdin to stdout:

.. code-block:: bash

   expression_generator |  rdg | data_handling_program
