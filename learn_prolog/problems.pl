
my_last([X], X) :- true.
my_last([_ | Tail], X)
  :- my_last(Tail, X).


last_but_not([X, _], X).
last_but_not([_, Y | Yh], X) :-
  last_but_not([Y | Yh], X).


element_at(Ret, [Ret | _], 1).
element_at(Ret, [_ | Tail], Where) :-
  Where > 1, Where1 is Where - 1, element_at(Ret, Tail, Where1).

length_list(0, []).
length_list(Len, [_ | Tail]) :-
  length_list(Len1, Tail), Len is Len1 + 1.


reverse_list(L1, L2) :- my_reverse(L1, L2, []).

my_reverse([], List2, List2) :- !.
my_reverse([Head | Tail], List2, Acc) :-
  my_reverse(Tail, List2, [Head | Acc]).


/*Find out whether a list is palindrome */

is_palindrome(L) :-
  reverse_list(L, L).

my_flatten(X,[X]) :- \+ is_list(X).
my_flatten([],[]).
my_flatten([X|Xs],Zs) :- my_flatten(X,Y), my_flatten(Xs,Ys), append(Y,Ys,Zs).

