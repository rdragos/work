open Printf

let at x list =

  let rec findme cur_idx l2 =
    match l2 with
    | [] -> None
    | y :: tail when (cur_idx = 0) -> Some y
    | _ :: tail -> findme (cur_idx - 1) (tail)
  in findme x list;;


let (|>>) x f =
  match x with
  | None -> ()
  | Some x -> f x;;

print_string "First\n";;
at 2 [3;4;5;6] |>> print_int;;
print_string "\n";;

let rec length list =
  match list with
  | [] -> 0
  | _ :: tail -> length(tail) + 1;;

print_string "Second\n";;
print_int(length [1;2;3;4]);;
print_string "\n";;

let rec print_list list =
  match list with
  | [] -> ()
  | head :: tail -> print_int head ; print_string " " ; print_list tail;;

(*  fact(i) = fact(i - 1) * i
    for (int i = 1; i <= n; ++i) acc = acc * i;
    fact(i, acc) = fact(i - 1, acc * i);
    fact(1, acc) -> acc;
    
    fact(n, 1);
*)

let reverse list =
  let rec aux acc sl =
    match sl with
    | [] -> acc
    | head :: tail -> aux (head :: acc) tail in
  aux [] list;;

print_string "Third\n";;
print_list( reverse [1;2;3;4;5] );;
print_string "\n";;

print_string "4'th\n";;

let is_palindrome list =
  if list = (reverse list) then true
  else false;;

printf "%B\n" (is_palindrome [1;2;1]);;
printf "%B\n" (is_palindrome [ "x" ; "a" ; "m" ; "a" ; "x" ]);;
printf "%B\n" (not (is_palindrome [ "a" ; "b" ]));;

print_string "5'th\n";;
(* There is no nested list type in OCaml, so we need to define one
  first. A node of a nested list is either an element, or a list of
  nodes.
*)
type 'a node =
  | One of 'a
  | Many of 'a node list;;

let flatten list =
  let rec aux acc x =
    match x with
    | [] -> acc
    | One x :: t -> aux (x :: acc) t
    | Many l :: t -> aux (aux acc l) t in
  List.rev(aux [] list);;

(*
 * First version
let compress list =
  let rec aux acc last x =
    match x with
    | [] -> acc
    | h :: t when not(h = last) -> aux (h :: acc) h t
    | h :: t -> aux acc last t in
  List.rev (aux [] "z" list);;
*)

let rec compress list =
  match list with
  | a :: (b :: _ as t) -> if a = b then compress t else a :: compress t
  | smaller -> smaller;;

(*
let pack list =
  let rec aux w_list cur_list list =
    match list with
    | [] -> []
    | [x] -> w_list :: (x cur_list)
    | a :: (b :: _ as t) ->
        if a = b then aux w_list (a :: cur_list) t
        else aux (w_list :: cur_list) [] t in
  List.rev(aux [] [] list);;
*)

type 'a rle =
  | Many of int * 'a
  | One of 'a;;


let encode list =

  let create_tuple cnt a =
    if cnt = 1 then One(a)
    else Many (cnt,a) in

  let rec inner list count acc =
    match list with
    | [] -> []
    | [x] -> (create_tuple (count+1) x) :: acc
    | a :: (b :: _ as t) ->
        if a = b then inner t (count+1) acc
        else inner t 0 ((create_tuple (count + 1) a) ::acc) in
  List.rev(inner list 0 []);;

let decode list =
  let rec gen_rec x y acc =
    match x with
    | 0 -> acc
    | x -> gen_rec (x - 1) y (y :: acc) in
  let gen_list x acc =
    match x with
    | One x -> x::acc
    | Many (a, b) -> gen_rec a b acc in
  let rec inner list acc =
    match list with
    | [] -> acc
    | h :: t -> inner t (gen_list h acc) in
  List.rev(inner list []);;

let decode list =
  let rec generate how_many putc acc =
    match how_many with
    | 0 -> acc
    | x -> generate (x - 1) putc (putc :: acc) in
  let rec inner list acc =
    match list with
    | [] -> acc
    | One x :: t -> inner t (x :: acc)
    | Many (x, y) :: t -> inner t (generate x y acc) in
  List.rev(inner list []);;


let duplicate list =
  let rec inner list acc =
    match list with
    | [] -> acc
    | h :: t -> inner t (h :: h :: acc) in
  List.rev(inner list []);;

let replicate list how_many =
  let rec multiply putc n acc =
    match n with
    | 0 -> acc
    | x -> multiply putc (x - 1) (putc :: acc) in

  let rec inner list acc =
    match list with
    | [] -> acc
    | h :: t -> inner t (multiply h how_many acc) in
  List.rev(inner list []);;

let drop list how_many =
  let rec inner list idx acc =
    match list with
    | [] -> acc
    | h :: t -> if idx = how_many then inner t 1 acc else inner t (idx + 1) (h :: acc) in
  List.rev(inner list 1 []);;


let split list limit =
  let rec inner list idx acc =
    match list with
    | [] -> List.rev(acc), []
    | h :: t as l -> if idx > 0 then inner t (idx - 1) (h :: acc) else List.rev(acc), l in
  inner list limit [];;

(*Extract a slice from a list*)
let slice list lim1 lim2 =
  let rec inner list idx acc =
    match list with
    | [] -> acc
    | h :: t ->
        if idx >= lim1 && idx <= lim2 then inner t (idx + 1) (h::acc)
        else inner t (idx + 1) acc in
  List.rev(inner list 0 []);;

(*Rotate a list N places to the left.*)
(*a[i] <- a[(i + r)% n]*)

let rotate list where =
  let len = List.length list in
  let n = if len = 0 then 0 else (where mod len + len) mod len in
  if n = 0 then list
  else let a, b = split list n in b @ a;;

(*Remove the K'th element from a list.*)
let remove_at idx list =
  let rec inner cidx list acc =
    match list with
    | [] -> acc
    | h :: t ->
        if cidx = idx then inner (cidx + 1) t acc
        else inner (cidx + 1) t (h :: acc) in
  List.rev(inner 0 list []);;

(*20. Insert an element at a given position into a list.*)

let insert_at x pos list =
  let pos = min (List.length (list)) pos in
  let rec inner list idx acc =
    match list with
    | [] -> if idx = pos then x :: acc else acc
    | h :: t ->
        if idx = pos then inner t (idx + 1) (h :: x :: acc)
        else inner t (idx + 1) (h :: acc) in
  List.rev(inner list 0 []);;

(*21. Create a list containing all integers within a given range*)
let range x y =
  let rec gen it y acc =
    match it with
    | el -> if el <= y then gen (it + 1) y (el :: acc) else acc in
  if x < y then List.rev(gen x y [])
  else gen y x [];;

(*22. Extract a given number of randomly selected elements from a list. *)

let rand_select list how_many =
  let rec selectidx list idx acc =
    match list with
    | [] -> raise Not_found
    | h :: t -> if idx = 0 then (h, acc @ t) else selectidx t (idx - 1) (h :: acc) in
  let aux list where =
    selectidx list where [] in
  let rec select how_many list len acc =
    match how_many with
    | 0 -> acc
    | x ->
        let picked, rest = aux list (Random.int len) in
        select (how_many - 1) rest (len - 1) (picked :: acc) in
  select how_many list (List.length list) [];;

(*23. Lotto: Draw N different random numbers from the set 1..M*)
let lotto_select n m =
  rand_select (range 1 m) n;;

(*Generate a random permutation of the elements of a list.*)
let permutation list =
  rand_select list (List.length list);;

(*Generate the combinations of K distinct objects chosen from the N*)

let extract n list =
  let mem solutions =
    let rec inner where list acc =
      match list, where with
      | _, 0 -> (List.rev acc) :: solutions
      | [], y -> []
      | head::tail, y ->
          (inner (y - 1) tail (head::acc)) @ (inner y tail acc )in
    inner n list []
  in mem [];;

