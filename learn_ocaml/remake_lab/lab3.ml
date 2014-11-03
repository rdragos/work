open String;;

type log =
   Bool of bool
  | Not of log
  | And of log * log
  | Var of string;;

let e1 = Not(And(Not (Bool true), Not (Bool false)))

let e2 = And(Not(And(Not (Bool true), Not (Var "x"))), Var "y")
(*
 * !( !(true) && !x ) && y
 * !( false && !x) && y
 * true && y
*)
let string_of_log exp =
  let rec aux exp =
    match exp with
    | Not e -> String.concat " " ["!("; aux e; ")"]
    | And(x,y) -> String.concat " " [aux x; "&&"; aux y]
    | Bool b -> if b = true then "true" else "false"
    | Var x -> x in
  aux exp;;

let eval exp =
  let rec aux exp =
    match exp with
    | Var x -> raise (Failure "Expresia are variabile")
    | Bool b -> b
    | Not e -> not(aux e)
    | And(x, y) -> (aux x) && (aux y) in
  aux exp;;

let evalueaza varlist exp =
  let rec aux exp =
    match exp with
    | Var x -> List.assoc x varlist
    | Bool b -> b
    | Not e -> not(aux e)
    | And(x, y) -> (aux x) && (aux y) in
  aux exp;;

let simplifica exp =
  let rec aux exp =
    match exp with
    | Var x -> Var x
    | And(x, y) -> (
        match aux x, aux y with
        | (Bool false, _) -> Bool false
        | (_, Bool false) -> Bool false
        | (a, b) -> And(a, b)
      )
    | Not e ->
        (match aux e with
          | (Bool true) -> (Bool false)
          | (Bool false) -> (Bool true)
          | rest -> (Not rest)
        )
    | Bool b -> Bool b  in
  aux exp;;

let transformator f exp =
  let rec aux exp =
    match exp with
    | Var x -> f (Var x)
    | And(x, y) -> f (And((aux x), (aux y)))
    | Not x -> f (Not (aux x))
    | Bool b -> f (Bool b) in
  aux exp;;

let simplific_trans exp =
  let lambda = function
    | And(Bool true, Bool false) -> (Bool false)
    | And(Bool false, Bool true) -> (Bool false)
    | l -> l in
  transformator lambda exp;;

(* 7* ...TODO *)
