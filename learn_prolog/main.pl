hello_world :- write('Hello World!').


write_list([]).
write_list([A | B]) :- write(A), write(' '), write_list(B).

abs(X, Y) :- X < 0, Y is -X.
abs(X, X) :- X >= 0.

second([_, X | _], X).


/* Concat 2 lists */
concat([], Acc, Acc).
concat([Head | Tail], List, [Head | Acc]) :- concat(Tail, List, Acc).


/* Verify if a list is a set */
set_verify([], true).
set_verify([Head | Tail], Answer) :-
   member(Head, Tail) -> set_verify([], false); set_verify(Tail, Answer).

/*transform list into a set*/

list_to_set([], []).
list_to_set([Head | Tail], A


