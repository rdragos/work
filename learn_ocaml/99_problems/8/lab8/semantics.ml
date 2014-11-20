open Mem
open ImpAST

let rec reduce = function
  | (Op(Float(n1, l1), op, Int(n2, l2), loc), s)
    -> Some(Op(Float(n1, l1), op, Float(float_of_int n2, l2), loc), s)

  | (Op(Int(n1, l1), op, Float(n2, l2), loc), s)
    -> Some(Op(Float(float_of_int n1, l1), op, Float(n2, l2), loc), s)

  | (Op(Float(n1, _), Plus, Float(n2, _), loc), s) -> Some(Float(n1+.n2, loc), s) 
  | (Op(Float (n1,_),Minus,Float (n2,_),loc),s) -> Some (Float (n1-.n2,loc),s) 
  | (Op(Float (n1,_),Mul,Float (n2,_),loc),s) -> Some (Float (n1*.n2,loc),s)             

  | (Op(Float (n1,_),Div,Float (n2,_),loc),s) when n2 <> 0.0
    -> Some (Float (n1/.n2,loc),s)


  | (Op(Int (n1,_),Plus,Int (n2,_),loc),s) -> Some (Int (n1+n2,loc),s)             (*Op+*)
  | (Op(Int (n1,_),Minus,Int (n2,_),loc),s) -> Some (Int (n1-n2,loc),s)             (*Op+*)
  | (Op(Int (n1,_),Mul,Int (n2,_),loc),s) -> Some (Int (n1*n2,loc),s)             (*Op+*)
  | (Op(Int (n1,_),Div,Int (n2,_),loc),s) when n2 <> 0 
    -> Some (Int (n1/n2,loc),s)             (*Op+*)

  | (Op(Int (n1,_),Mic,Int (n2,_),loc),s) -> Some (Bool (n1<=n2,loc),s)            (*Op<=*)
  | (Op(Int (n1,_),Egal,Int (n2,_),loc),s) -> Some (Bool (n1=n2,loc),s)            (*Op<=*)
  | (Op(Float(n1,_),Mic,Float(n2,_),loc),s) -> Some (Bool (n1<=n2,loc),s)            (*Op<=*)
  | (Op(Float(n1,_),Egal,Float(n2,_),loc),s) -> Some (Bool (n1=n2,loc),s)            (*Op<=*)

  | (Op(Int (n1,loc1),op,e2,loc),s) ->                                        (*OpD*)
    (match reduce (e2,s) with 
      | Some (e2',s') -> Some (Op(Int (n1,loc1),op,e2',loc),s')
      | None -> None
    )

  | (Op(Float(n1,loc1),op,e2,loc),s) ->                                        (*OpD*)
    (match reduce (e2,s) with 
      | Some (e2',s') -> Some (Op(Float (n1,loc1),op,e2',loc),s')
      | None -> None
    )

  | (Op(e1,op,e2,loc),s) ->                                            (*OpS*)
    (match reduce (e1,s) with Some (e1',s') -> Some (Op(e1',op,e2,loc),s')
      | None -> None)
  | (Loc (l,loc), s) -> Some (Int (lookup l s,loc), s)                    (*Loc*)
  | (Atrib(l, Int (n,_),loc),s) ->                                         (*Atrib*)
      Some (Skip loc, update (l,n) s)
  | (Atrib(l,e,loc),s) ->                                          (*AtribD*)
    (match reduce (e,s) with Some (e',s') -> Some (Atrib(l,e',loc),s')
      | None -> None)
  | (Secv(Skip _,e,_),s) -> Some (e,s)                                 (*Secv*)
  | (Secv(e1,e2,loc),s) ->                                             (*SecvS*)
    (match reduce (e1,s) with Some (e1',s') -> Some (Secv(e1',e2,loc),s')
      | None -> None)
  | (If(Bool (true,_),e1,e2,_),s) -> Some (e1,s)                         (*IfTrue*)
  | (If(Bool (false,_),e1,e2,_),s) -> Some (e2,s)                        (*IfFalse*)
  | (If(e,e1,e2,loc),s) ->                                             (*IfS*)
    (match reduce (e,s) with Some (e',s') -> Some (If(e',e1,e2,loc),s')
      | None -> None)
  | (While(e1,e2,loc),s) -> Some (If(e1,Secv(e2,While(e1,e2,loc),loc),Skip loc,loc),s) (*While*)
  | (For(init,cond,incr,body,l), s) 
    -> Some (Secv(init,While(cond,Secv(body,incr,l),l),l), s)    (*For*)
  | _ -> None                                                    (*default*)


(* evaluate basically computes the transitive closure ->* of the
   one step reduction relation. *)
let rec evaluate c = match (reduce c) with
  | Some c -> evaluate c
  | None -> c


let string_of_config (p,m) = "<" ^ string_of_expr p ^ ", {" ^ string_of_mem m ^ "} >"
