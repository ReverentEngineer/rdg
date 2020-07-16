Expressions
======================

RDG currently only supports a subset of `regular expressions`_ although that may
expand as other construct prove value in this use-case. The current supported
constructs are: literals, bracket expressions, boolean "or", and groups

It can be represented in `Augmented Backus-Naur form`_ as:

.. code-block::

  <expression>         ::= <branch>
  <branch>             ::= <component> | <branch> <component>
  <component>          ::= <backet_expression> | <group> | <literal>
  <bracket_expression> ::= <bracket_component> | <bracket_expresion> <bracket_component>
  <bracket_component>  ::= <range> | <literal>
  <range>              ::= <literal> "-" <literal>
  <group>              ::= "(" <branches> ")" 
  <branches>           ::= <branch> | <branches> "|" <branch>
  <literal>            ::= <digit> | <letter> | <byte> 
  <byte>               ::= "\x" <nibble> <nibble>
  <nibble>             ::= <digit> | %x41-46 | %x61-56
  <digit>              ::= %x30-39
  <letter>             ::= %x41-5A | %x61-7A 

.. _Augmented Backus-Naur form: https://en.wikipedia.org/wiki/Augmented_Backus–Naur_form
.. _regular expressions: https://en.wikipedia.org/wiki/Regular_expression


Literals
--------------------

Literals are the simplest constructs. They represent a single byte character
represented in character form or byte form. Character form is, as one might
expect, a literal character such as 'a' or '1'. Byte form is a four character 
string that represents a single byte such as '\\x00' or '\\xff'.

Examples of valid literals include:

.. code-block::

   "g"
   "6"
   "\x00"

Bracket Expressions
--------------------

Bracket expressions match any single literal within the bracket. These
expressions can list out every literal, use a range, or both. A range of the
form, of the form `<from>-<to>`, selects all literals in consecutive range
from the former to the latter.

Examples of valid ranges include:

.. code-block::

   "[agz]"  # Generates the characters 'a', 'g', and 'z'
   "[a-d]"  # Generates the characters 'a', 'b', 'c', and 'd'
   "[b1-3]" # Generates the characters 'b', '1', '2', '3'

Boolean "or"
--------------------

Boolean "or" allows for expressions to have multiple non-overlapping options.

Examples of valid boolean "or" expressions include:

.. code-block::

   "sheep|lamb" # Generates "sheep" or "lamb"
   "red|blue|green" # Generates "red", "blue", and "green"


Groups
--------------------

Groups are a way of defining scope and precedence. In standard regular 
expressions, groups are split into capture and non-capture
groups. Currently, all groups in RDG are non-capture as it doesn't implement
the capture construct.

Examples of groups include:

.. code-block::

  "hello (world|earth)" # Generates "hello world" and "hello earth"
  "hello (my|our) friend" # Generates "hello my friend" and "hello our friend"


