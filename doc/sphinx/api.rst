API
=====

.. c:struct:: rdg

   The regex data generator object representing the state of the generation.

.. c:function:: const char* rdg_get_version()
  
    Gets the version string

    :returns: A pointer to the static version string

.. c:function:: struct rdg* rdg_new(const char *expression)

    Creates a new data generator based off the provided expression. The returned
    object stores the state of the generator. It is the application's responsibility
    to free with :c:func:`rdg_free`.

    :returns: An instance of :c:struct:`rdg`

.. c:function:: int rdg_generate(unsigned char **result, size_t *size, struct rdg* rdg)

   :returns: 1 on success, or 0 if no permutations remain

   .. warning::
   
      This is not thread-safe.

.. c:function:: size_t rdg_permutations(struct rdg* rdg)

  Calculates the number of permutations

  :returns: The number of permutations

  .. note::
     This is the total number of permutations NOT the number remaining

.. c:function:: void rdg_free(struct rdg* rdg)

   Frees the data generator object
