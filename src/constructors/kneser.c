/*
   IGraph library.
   Copyright (C) 2022  The igraph development team

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301 USA
*/

#include "igraph_vector_list.h"

static igraph_integer_t igraph_i_number_of_subsets(igraph_integer_t n, igraph_integer_t k){
    igraph_integer_t r = (k < n - k ? k : n - k);
    igraph_integer_t number_of_subsets = 1;

    for(igraph_integer_t i = 1 ; i <= r ; i++) {
        number_of_subsets *= n - i + 1;
        number_of_subsets /= i;
    }

    return number_of_subsets;
}

static igraph_error_t igraph_i_generate_subsets(igraph_integer_t n, igraph_integer_t k,
                              igraph_integer_t subsets, igraph_vector_int_list_t *vertices) {

    igraph_vector_int_t *temp = igraph_vector_list_get_ptr(vertices, 0);
    IGRAPH_CHECK(igraph_vector_resize(temp, k));
    for(igraph_integer_t i = 0 ; i < k ; i++) {
        VECTOR(*temp)[i] = i + 1;
    }

    igraph_integer_t list_idx = 0, vector_idx = k - 1;
    while(list_idx < subsets - 1) {
        temp = igraph_vector_list_get_ptr(vertices, list_idx + 1);
        IGRAPH_CHECK(igraph_vector_resize(temp, k));

        IGRAPH_CHECK(igraph_vector_update(temp, igraph_vector_list_get_ptr(vertices, list_idx)));

        igraph_integer_t subset_pos = k - 1;
        while(subset_pos >= 0 && VECTOR(*temp)[subset_pos] == n - (k - 1 - subset_pos)) {
            subset_pos--;
        }

        VECTOR(*temp)[subset_pos]++;
        while(++subset_pos < k) {
            VECTOR(*temp)[subset_pos] = VECTOR(*temp)[subset_pos - 1] + 1;
        }

        list_idx++;
    }

    return IGRAPH_SUCCESS;
}