/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2012       Manuele Conti  (conti.ma@alice.it)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 */

#include "datatype_functions.hh"
#include "../absyntax_utils/absyntax_utils.hh"
#include <algorithm>





elementary_type_c *elementary_type_c::singleton = NULL;

const char *elementary_type_c::to_string(symbol_c *symbol) {
  if (NULL == singleton)    singleton = new elementary_type_c;
  if (NULL == singleton)    ERROR;
  const char *res           = (const char *)symbol->accept(*singleton);
  if (NULL == res) {
	  int i = 1;
  }
  return res;
}





/*
 * 2.5.1.5.6 Functions of time data types
 * Table 30 - page 64
 */

const struct widen_entry widen_ADD_table[] = {
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::tod_type_name,             &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::dt_type_name,              &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetod_type_name,         &search_constant_type_c::safetod_type_name  },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safedt_type_name,          &search_constant_type_c::safedt_type_name   },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetime_type_name,        &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetod_type_name  },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safetime_type_name,        &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safedt_type_name   },
    { NULL, NULL, NULL },
};


const struct widen_entry widen_SUB_table[] = {
	{ &search_constant_type_c::time_type_name,          &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name     },
	{ &search_constant_type_c::tod_type_name,           &search_constant_type_c::tod_type_name,             &search_constant_type_c::tod_type_name      },
	{ &search_constant_type_c::dt_type_name,            &search_constant_type_c::dt_type_name,              &search_constant_type_c::dt_type_name       },
	{ &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetime_type_name },
	{ &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetod_type_name,         &search_constant_type_c::safetod_type_name  },
	{ &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safedt_type_name,          &search_constant_type_c::safedt_type_name   },

	{ &search_constant_type_c::tod_type_name,           &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetime_type_name,        &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetod_type_name  },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safetime_type_name,        &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safedt_type_name   },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::tod_type_name,             &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::tod_type_name,             &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetod_type_name,         &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetod_type_name,         &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::date_type_name,          &search_constant_type_c::date_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safedate_type_name,      &search_constant_type_c::date_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::date_type_name,          &search_constant_type_c::safedate_type_name,        &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safedate_type_name,      &search_constant_type_c::safedate_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::dt_type_name,              &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::dt_type_name,              &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safedt_type_name,          &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safedt_type_name,          &search_constant_type_c::safetime_type_name },
    { NULL, NULL, NULL },
};

const struct widen_entry widen_MUL_table[] = {
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::lreal_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::real_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::dint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::int_type_name,             &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::sint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::ulint_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::udint_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::uint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::usint_type_name,           &search_constant_type_c::time_type_name     },

    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::lreal_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::real_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::dint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::int_type_name,             &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::sint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::ulint_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::udint_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::uint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::usint_type_name,           &search_constant_type_c::safetime_type_name },

    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safelreal_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safereal_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safedint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeint_type_name,         &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safesint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeulint_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeudint_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeuint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeusint_type_name,       &search_constant_type_c::safetime_type_name },

    { NULL, NULL, NULL },
};

const struct widen_entry widen_DIV_table[] = {
	{ &search_constant_type_c::time_type_name,          &search_constant_type_c::lreal_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::real_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::dint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::int_type_name,             &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::sint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::ulint_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::udint_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::uint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::usint_type_name,           &search_constant_type_c::time_type_name     },

    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::lreal_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::real_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::dint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::int_type_name,             &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::sint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::ulint_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::udint_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::uint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::usint_type_name,           &search_constant_type_c::safetime_type_name },

    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safelreal_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safereal_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safedint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeint_type_name,         &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safesint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeulint_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeudint_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeuint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeusint_type_name,       &search_constant_type_c::safetime_type_name },

    { NULL, NULL, NULL },
};

/* Search for a datatype inside a candidate_datatypes list.
 * Returns: position of datatype in the list, or -1 if not found.
 */
int search_in_candidate_datatype_list(symbol_c *datatype, std::vector <symbol_c *> candidate_datatypes) {
	if (NULL == datatype) 
		return -1;

	for(unsigned int i = 0; i < candidate_datatypes.size(); i++)
		if (is_type_equal(datatype, candidate_datatypes[i]))
			return i;
	/* Not found ! */
	return -1;
}





/* Copy the elements in the candidate_datatype_list in one symbol (from)
 * into the candidate_datatype_list of another symbol (to)
 */
void copy_candidate_datatype_list(symbol_c *from, symbol_c *to) {
	if ((NULL == from) || (NULL == to))
		return;
	for(unsigned int i = 0; i < from->candidate_datatypes.size(); i++)
		to->candidate_datatypes.push_back(from->candidate_datatypes[i]);
	/* for some reason, the following alternative implementation results in a segmentation fault! I am not going to bother with this for now! */
// 	std::copy(from->candidate_datatypes.begin(), from->candidate_datatypes.end(), to->candidate_datatypes.begin());
}





/* A helper function... */
bool is_ANY_ELEMENTARY_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_MAGNITUDE_type(type_symbol)
      || is_ANY_BIT_type      (type_symbol)
      || is_ANY_STRING_type   (type_symbol)
      || is_ANY_DATE_type     (type_symbol);
}

/* A helper function... */
bool is_ANY_SAFEELEMENTARY_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEMAGNITUDE_type(type_symbol)
      || is_ANY_SAFEBIT_type      (type_symbol)
      || is_ANY_SAFESTRING_type   (type_symbol)
      || is_ANY_SAFEDATE_type     (type_symbol);
}

/* A helper function... */
bool is_ANY_ELEMENTARY_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  /* NOTE: doing
   *          return is_ANY_SAFEELEMENTARY_type() || is_ANY_ELEMENTARY_type()
   *       is incorrect, as the literals would never be considered compatible...
   */
  return is_ANY_MAGNITUDE_compatible(type_symbol)
      || is_ANY_BIT_compatible      (type_symbol)
      || is_ANY_STRING_compatible   (type_symbol)
      || is_ANY_DATE_compatible     (type_symbol);
}


/* A helper function... */
bool is_ANY_MAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
  return is_ANY_NUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_MAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
  return is_ANY_signed_NUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_SAFEMAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c)) {return true;}
  return is_ANY_SAFENUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_SAFEMAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c)) {return true;}
  return is_ANY_signed_SAFENUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_MAGNITUDE_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEMAGNITUDE_type(type_symbol))              {return true;}
  return is_ANY_NUM_compatible(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_signed_MAGNITUDE_type    (type_symbol))       {return true;}
  if (is_ANY_signed_SAFEMAGNITUDE_type(type_symbol))       {return true;}
  return is_ANY_signed_NUM_compatible(type_symbol);
}

/* A helper function... */
bool is_ANY_NUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type(type_symbol))                       {return true;}
  if (is_ANY_INT_type(type_symbol))                        {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_NUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type(type_symbol))                       {return true;}
  if (is_ANY_signed_INT_type(type_symbol))                 {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFENUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEREAL_type(type_symbol)
      || is_ANY_SAFEINT_type (type_symbol);
}

/* A helper function... */
bool is_ANY_signed_SAFENUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEREAL_type(type_symbol)
      || is_ANY_signed_SAFEINT_type (type_symbol);
}

/* A helper function... */
bool is_ANY_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_compatible(type_symbol))                       {return true;}
  if (is_ANY_INT_compatible(type_symbol))                        {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_compatible(type_symbol))                       {return true;}
  if (is_ANY_signed_INT_compatible(type_symbol))                 {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_DATE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(date_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(tod_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(dt_type_name_c))   {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEDATE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safedate_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safetod_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safedt_type_name_c))   {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_DATE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_DATE_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEDATE_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_STRING_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(string_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(wstring_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFESTRING_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safestring_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safewstring_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_STRING_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_STRING_type    (type_symbol))              {return true;}
  if (is_ANY_SAFESTRING_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_INT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(usint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(uint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(udint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(ulint_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_INT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_SAFEINT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safesint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safedint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelint_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEINT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safesint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safedint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeusint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safeuint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeudint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safeulint_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_signed_INT_type    (type_symbol))              {return true;}
  if (is_ANY_signed_SAFEINT_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_INT_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEINT_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_REAL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(real_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lreal_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEREAL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safereal_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelreal_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_REAL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEREAL_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BIT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(byte_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(word_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(dword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(lword_type_name_c))    {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEBIT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safebyte_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safeword_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safedword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safelword_type_name_c))    {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BIT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_BIT_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEBIT_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_BOOL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))      {return true;}
  return false;
}

/* A helper function... */
bool is_SAFEBOOL_type(symbol_c *type_symbol){
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BOOL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_BOOL_type    (type_symbol))              {return true;}
  if (is_SAFEBOOL_type(type_symbol))              {return true;}
  return false;
}





bool is_type_equal(symbol_c *first_type, symbol_c *second_type)
{
    if (first_type == NULL || second_type == NULL) {
        return false;
    }
    if (is_ANY_ELEMENTARY_type(first_type)) {
        if (typeid(*first_type) == typeid(*second_type))
            return true;
    } else   /* ANY_DERIVED */
        return (first_type == second_type);

    return false;
}