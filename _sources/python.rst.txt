Python Bindings
=================

The Python bindings is designed to be simple.

.. py:class:: RDG(expression)

   The RDG object is an iterator that generates the permutations of the regular
   expression provided by the application.

   .. code-block:: python

      from rdg import RDG
      for permutation in RDG("test[1-3][a-c]"):
        print(permutation)
