/*First Exercise */
concat_list([], List, List).
concat_list([Head | Tail], List, [Head | Acc]) :-
  concat_list(Tail, List, Acc).

/*Verify if a list is a set */

is_set([]).
is_set([X|Y]) :-
  \+ member(X, Y), is_set(Y).

/* Transform a list into a set */

list_to_set(L, R) :-
  aux_set(L, R, []).

aux_set([], Acc, Acc).
aux_set([X | T], R, Acc) :-
  \+ member(X, Acc) -> aux_set(T, R, [X | Acc])
  ; aux_set(T, R, Acc).

/* Intersection, Union, Difference of 2 sets */

set_intersection(L1, L2, R) :-
  set_intersection_aux(L1, L2, R, []).

set_intersection_aux([], _, R, Acc) :-
  list_to_set(Acc, R).

set_intersection_aux([H | Tail], L2, R, Acc) :-
  member(H, L2) -> set_intersection_aux(Tail, L2, R, [H | Acc]);
  set_intersection_aux(Tail, L2, R, Acc).

/*Set union */

set_union(L1, L2, R) :-
  concat_list(L1, L2, R2), list_to_set(R2, R).

/*Set difference */
set_difference(L1, L2, R) :-
  set_difference_aux(L1, L2, R, []).

set_difference_aux([], _, R, Acc) :-
  list_to_set(Acc, R).
set_difference_aux([H | T], L2, R, Acc) :-
  \+ member(H, L2) -> set_difference_aux(T, L2, R, [H | Acc]);
  set_difference_aux(T, L2, R, Acc).


/*Insert element to the beggining of a list if there isn't in the List */

insert_beg(L, [], L).
insert_beg(X, L, L) :- member(X, L).
insert_beg(X, L, Y) :- \+member(X, L), concat_list([X], L, Y).

/*Erase an element from a list */

erase_element(_, [], []).

erase_element(X, [X | T], L) :- erase_element(X, T, L).
erase_element(X, [H | T], [H | Ret]) :- X \= H, erase_element(X, T, Ret).

/*Compute fact(n) then fib(n) */

factorial(N, Ret) :-
  aux_factorial(N, Ret, 1).

aux_factorial(1, Acc, Acc).
aux_factorial(N, Ret, Acc) :-
  N > 1, N2 is (N - 1), Acc2 is (Acc * N), aux_factorial(N2, Ret, Acc2).


fib(N, Ret) :-
  aux_fib(N, Ret, 0, 1).

aux_fib(0, Current, _, Current).
aux_fib(N, Ret, Prev, Current) :-
  N > 0, N2 is (N - 1), Current2 is (Current + Prev), Prev2 is Current, aux_fib(N2, Ret, Prev2, Current2).

/*gcd(a, b) = gcd(b, a % b) */
gcd(A, B, Ret) :-
  aux_gcd(A, B, Ret).

aux_gcd(A, 0, A).
aux_gcd(A, B, Ret) :-
  A2 is mod(A, B), aux_gcd(B, A2, Ret).

/* compute the length of a list */

my_length(L, Ret) :-
  aux_length(L, 0, Ret).

aux_length([], Acc, Acc).

aux_length([_ | T], Len, Ret) :-
   Len2 is Len + 1, aux_length(T, Len2, Ret).

/* compute sum of positive integers from a list */

positive_sum(L, Ret) :-
  aux_positive_sum(L, 0, Ret).

aux_positive_sum([], Acc, Acc).
aux_positive_sum([H | T], Acc, Ret) :-
  H > 0 -> (Acc2 is Acc + H, aux_positive_sum(T, Acc2, Ret));
  aux_positive_sum(T, Acc, Ret).

