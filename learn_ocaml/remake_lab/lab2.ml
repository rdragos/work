(* Funcții de ordin înalt *)

(* 1 *)

let fa x = 3 * x;;
let ga x = x * x;;
let f2 x y = x + y;;
let f1 (x,y) = x + y;;

let plus f g x =
  f x + g x;;

let ha = plus fa ga;;
ha 5;; 
(* 2 *)

let lift orig f g = function x -> orig (f x) (g x);;
let plus1 = lift f2;;
plus1 fa ga 5;;

let op1 x y = x * y + x + y;;
let fop1 = lift op1;;
let hb = fop1 fa ga;;
hb 5;;

(* 3 *)

let compune f g = function x -> f (g x);;
let hc = compune fa ga;;
hc 5;;


(* Functii recursive *)

(* 1 *)

let rec factorial n =
  match n with
  | 0 -> 1
  | x -> x * factorial (x - 1);;

factorial 3;;

(* 2 *)
let rec fib n =
  match n with
  | 0 -> 0
  | 1 -> 1
  | x -> fib(x - 2) + fib(x - 1);;

fib(5);;

(* 2* - tail recursion mode *)
let fib n =
  let rec aux x y many =
    match many with
    | 1 -> y
    | _ -> aux y (x + y) (many - 1) in
  aux 0 1 n;;

fib(5);;

(* Recursie pe liste *)
(* 1 *)

let prim list =
  match list with
  | h :: _ -> h
  | _ -> raise (Failure ("Lista este vida"));;

prim ["a";"b";"c"];;

(* 2 *)
let rec ultim list =
  match list with
  | [] -> raise (Failure "Lista este vida")
  | [x] -> x
  | h :: t -> ultim t;;

ultim ["a";"b";"c"];;

(* 2* *)
let rec penultim list =
  match list with
  | [] -> raise (Failure "Lista este vida")
  | [x] -> raise (Failure "Lista nu are suficiente elemente")
  | [a; b] -> a
  | h :: t -> penultim t;;

(* 3 *)
let lungime list =
  let rec aux list len =
    match list with
    | [] -> len
    | h :: t -> aux t (len + 1) in
  aux list 0;;

(* 4 - this can be done with list1 @ list2 *)
let lipeste list1 list2 =
  let rec inner list1 list2 acc =
    match (list1, list2) with
    | ([], []) -> acc
    | ([], h :: t) -> inner [] t (h :: acc)
    | (h :: t, l2) -> inner t l2 (h :: acc) in
  List.rev (inner list1 list2 []);;

(* 5 *)
let inverseaza list =
  let rec inner list acc =
    match list with
    | [] -> acc
    | h :: t -> inner t (h :: acc) in
  inner list [];;

(* 6 *)
let apartine el list =
  let rec aux el list =
    match list with
    | [] -> false
    | h :: t -> if h = el then true else aux el t in
  aux el list;;

(* 7 *)
let afla el list =
  let rec aux el list acc =
    match list with
    | [] -> acc
    | (a,b) :: t ->
        if a = el then
          aux el t (acc + b)
        else aux el t acc in
  aux el list 0;;

let pozitie where list =
  let rec aux idx list =
    match list with
    | [] -> -1;
    | h :: t -> if idx = where then h else aux (idx + 1) t in
  aux 1 list;;

let interclaseaza list1 list2 =
  let rec aux list1 list2 acc =
    match list1, list2 with
    | [], list2 -> List.rev list2 @ acc
    | list1, [] -> List.rev list1 @ acc
    | (h1 :: t1), (h2 :: t2) ->
        if h1 < h2 then aux t1 list2 (h1 :: acc)
        else aux list1 t2 (h2 :: acc) in
  List.rev (aux list1 list2 []);;

let divide list =
  let rec aux list acc1 acc2 =
    match list with
    | [] -> (acc1, acc2)
    | (a :: b :: t) -> aux t (a :: acc1) (b :: acc2)
    | [a] -> aux [] (a :: acc1) acc2 in
  aux list [] [];;

let inter_sort list =
  let rec aux = function
    | [] -> []
    | [_] as list -> list
    | all -> let l1, l2 = divide all in
      interclaseaza (aux l1) (aux l2) in
  aux list;;




