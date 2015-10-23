
reverse(L1, Ret) :-
  aux_reverse(L1, [], Ret).

aux_reverse([], Acc, Acc).
aux_reverse([Head | Tail], Acc, Ret) :-
  aux_reverse(Tail, [Head | Acc], Ret).

/* Ex1 */

replace(L, From, To, Ret) :-
  inner_replace(L, From, To, [], Ret).

inner_replace([], _, _, Acc, Ret) :-
  reverse(Acc, Ret).

inner_replace([H | T], From, To, Acc, Ret) :-
  (H = From) -> inner_replace(T, From, To, [To | Acc], Ret);
  inner_replace(T, From, To, [H | Acc], Ret).


replace1(L, From, To, Ret) :-
  inner_replace1(L, From, To, [], Ret).


inner_replace1([], _, _, Acc, Ret) :-
  reverse(Acc, Ret).

inner_replace1([H | T], From, To, Acc, Ret) :-
  (H = From) -> inner_replace2(T, [To | Acc], Ret);
  inner_replace1(T, From, To, [H | Acc], Ret).

inner_replace2([], Acc, Ret) :-
  reverse(Acc, Ret).

inner_replace2([H | T], Acc, Ret) :-
  inner_replace2(T, [H | Acc], Ret).
/*Ex 2 - done as a subroutine for Ex1*/

/*Ex 3 */

min_list([], _) :-
  fail.
min_list([Head | Tail], Ret) :-
  aux_min_list(Tail, Head, Ret).

aux_min_list([], Acc, Acc).
aux_min_list([Head | Tail], Acc, Ret) :-
  (Head < Acc) -> aux_min_list(Tail, Head, Ret);
  aux_min_list(Tail, Acc, Ret).


/*Ex 4 */

find_element(L, Poz, Ret) :-
  aux_find_el(L, Poz, Ret).

aux_find_el([], _, _) :-
  fail.

aux_find_el([Head | Tail], Poz, Ret) :-
  Poz > 1 -> (Poz2 is Poz - 1, aux_find_el(Tail, Poz2, Ret));
  Poz > 0, Ret = Head.

/*Ex 5 */

insert_at(L, Poz, What, Ret) :-
  aux_insert_el(L, Poz, What, [], Ret).

aux_insert_el([], Poz, What, Acc, Ret) :-
  (Poz = 1) -> reverse([What | Acc], Acc2), Ret = Acc2;
  fail.

aux_insert_el([Head | Tail], Poz, What, Acc, Ret) :-
  (Poz > 1) -> (Poz2 is Poz - 1, aux_insert_el(Tail, Poz2, What, [Head | Acc], Ret));
  (reverse([What | Acc], Acc2), append(Acc2, [Head | Tail], Ret)).

/* Ex 6 */
merge_lists(L1, L2, Ret) :-
  aux_merge_lists(L1, L2, [], Ret).

aux_merge_lists([], [], Acc, Ret) :-
  reverse(Acc, Ret).

aux_merge_lists([Head | Tail], [], Acc, Ret) :-
  aux_merge_lists(Tail, [], [Head | Acc], Ret).

aux_merge_lists([], [Head | Tail], Acc, Ret) :-
  aux_merge_lists([], Tail, [Head | Acc], Ret).

aux_merge_lists([Head1 | Tail1], [Head2 | Tail2], Acc, Ret) :-
  Head1 =< Head2 -> aux_merge_lists(Tail1, [Head2 | Tail2], [Head1 | Acc], Ret) ;
  (aux_merge_lists([Head1 | Tail1], Tail2, [Head2 | Acc], Ret)) .

/* Ex 7 */

partition(L, Pivot, R1, R2) :-
  aux_partition(L, Pivot, [], [], R1, R2).

aux_partition([], _, L1, L2, R1, R2) :-
  reverse(L1, R1), reverse(L2, R2).

aux_partition([Head | Tail], Pivot, L1, L2, R1, R2) :-
  (Head =< Pivot) -> aux_partition(Tail, Pivot, [Head | L1], L2, R1, R2);
  aux_partition(Tail, Pivot, L1, [Head | L2], R1, R2).