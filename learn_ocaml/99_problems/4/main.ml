open String;;

type hobby = Fotbal | Oina | Golf | Chitara;;

type log =
  | True
  | False
  | Var of string
  | Not of log
  | And of log * log
  | Or of log * log;;

type 'a option =
  | None
  | Some of 'a;;

type 'a lista =
  | Nil
  | Cons of 'a * ('a lista);;

let prim = function
  | Nil -> None
  | Cons(x, _) -> Some x;;

let e1 = And(Or(Var "x", Not(Var "y")), Var "z");;

let rec string_of_log x =
  match x with
  | Not y -> String.concat "!" ["("; string_of_log y; ")"]
  | And(y, z) -> String.concat "&" ["("; string_of_log y; string_of_log z; ")"]
  | Or(y, z) -> String.concat "|" ["("; string_of_log y; string_of_log z; ")"]
  | Var y -> y
  | True -> "True"
  | False -> "False";;

let rec simplifica x =
  match x with
  | True -> true
  | False -> false
  | Not y -> not (simplifica y)
  | And(y, z) -> simplifica y && simplifica z
  | Or(y, z) -> simplifica y || simplifica z
  | _ -> true;;

let e2 = And(Or(True, False), Not(False));;

let rec evalueaza list explog =

  let replace list:
    match list with
    | [] -> false
    | (name, value) :: t -> if name = var then value else atrib t

  let aux exp =
    match exp with
    | Not y -> not (aux y)
    | And(y, z) -> aux y && aux z
    | Or(y, z) -> aux y || aux z
    | Var y -> atrib y
    | True -> true
    | False -> false

simplifica e2;;
(* evalueaza 
