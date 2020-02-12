(* Brandon Kelley 2716916 Project 3 *)

(* In-Class functions *)

val _ = print "\n\n--------------------------------------------------------------------------------------"

val _ = print "\n\n\n\t\t\tCIS 424 Project 3\n\n";

val _ = print "\n\n\n\t\tDefine In-class given functions: \n\n";


(*appends two lists together*)
fun merge(nil, N) = N
  | merge(M, nil) = M
  | merge(M as x::xr, N as y :: yr) =
    if (x < y) then x::merge(xr,N)
    else y:: merge(M, yr);

(*maps a function to each element in a list*)
fun Map(F,nil) = nil
  |Map(F,x::xr) = F(x)::Map(F,xr);

(*takes a function and applies it to adjacent elements until 1 remains*)
exception EmptyList;
fun Reduce (F, nil) = raise EmptyList
  | Reduce(F,[a]) = a
  | Reduce (F,x::xr) = F(x,Reduce(F,xr));

(*filters elements out to new list of elements that pass condition*)
fun Filter (P,nil) = nil
  | Filter(P,x::xr)=
    if P(x) then x ::Filter(P,xr)
    else Filter(P,xr);



(* Problem 1 - Return the third element of a list. Assume that the length of the list is at least 3. *)

val _ = print "\n\n\n\n\t\t\tProblem 1: \n\n";


(*Use cons operator to get and return third element of list*)
fun returnThird (first::second::third::remaining) = third;


val _ = print "\n\n\tTest Case(s):\n\n";
val _ = print "returnThird [10,20,30];\n";
returnThird [10,20,30]; (*at least 3*)

val _ = print "\nreturnThird [10,20,30,40,50];\n";
returnThird [10,20,30,40,50]; (*greater than 3*)



(* Problem 2 - Given a list, return that list with its second element deleted. Assume the length of the list is at
least 2. *)

val _ = print "\n\n\n\n\t\t\tProblem 2: \n\n";

(*use hd (gets first element) and tl (pops first element and returns remaining list))*)
  fun removeSecond (L) =
    if L = nil then nil
    else hd(L)::tl(tl(L));

val _ = print "\n\n\tTest Case(s):\n\n";
val _ = print "removeSecond [10,20];\n";
removeSecond [10,20]; (*at least two*)

val _ = print "\nreturnThird [10,20,30,40,50];\n";
removeSecond [10,20,30,40,50]; (*greater than two*)



(* Problem 3 - Given three integers, use nested if to produce a 2-tuple containing the smallest and largest,
i.e. (smallest,largest). Note that at most 3 comparisons will be made to find the solution. *)

val _ = print "\n\n\n\n\t\t\tProblem 3: \n\n";

(* 6 possible outcomes, 2 comparisons minimum and 3 maximum *)
fun minMaxOf3Ints(a:int, b:int, c:int) =
  if(a > b)
    then if (b > c)
      then (c,a) (* a > b & b > c, therefore a > c so c is min and a is max*)
    else if (c > a)
      then (b,c) (*a > b & b < c, since c > a the min is b and c is the max*)
      else (b,a) (*a > b & b < c, since c < a the min is b and a is the max*)
  else if (a > c)
      then (c,b) (* b > a & a > c, therefore b > c so c is min and b is max*)
    else if (c > b)
      then (a,c) (* b > a & a < c, since c > b the min is a and c is the max*)
      else (a,b); (* b > a & a < c, since c < b the min is a and b is the max*)

val _ = print "\n\n\tTest Case(s):\n\n";

val _ = print "minMaxOf3Ints(10,20,30);\n"; (*min = a, max = c*)
minMaxOf3Ints(10,20,30);

val _ = print "\nminMaxOf3Ints(10,30,20);\n"; (*min = a, max = b*)
minMaxOf3Ints(10,30,20);

val _ = print "\nminMaxOf3Ints(30,20,10);\n"; (*min = c, max = a*)
minMaxOf3Ints(30,20,10);

val _ = print "\nminMaxOf3Ints(30,10,20);\n"; (*min = b, max = a*)
minMaxOf3Ints(30,10,20);

val _ = print "\nminMaxOf3Ints(20,10,30);\n"; (*min = b, max = c*)
minMaxOf3Ints(20,10,30);

val _ = print "\nminMaxOf3Ints(20,30,10);\n"; (*min = c, max = b*)
minMaxOf3Ints(20,30,10);



(* Problem 4 - Duplicate each element of a list. That is,given the list [a1,a2,...,an], produce the
list [a1,a1,a2,a2,...,an,an]. *)

val _ = print "\n\n\n\n\t\t\tProblem 4: \n\n";


fun  dupList nil = nil (* if the list is empty, return empty*)
  | dupList (L) = merge(hd(L)::tl(L), L); (*else merge the first element (hd) and remaing list (tl) with the list itself*)


val _ = print "\n\n\tTest Case(s):\n\n";

val _ = print "dupList [10,20,30,40,50];\n";
dupList [10,20,30,40,50];



(*Problem 5 - Use the function Map and an anonymous function to turn an integer list L into a list of reals, each of
which is the absolute value of the element in L. *)

val _ = print "\n\n\n\n\t\t\tProblem 5: \n\n";


fun convertToRealABS nil = nil (*if list is empty return empty*)
  | convertToRealABS (L) = (*else map the function to each number*)
    Map(fn x => if x < 0 then  ~ (real x) else (real x), L);

    val _ = print "\n\n\tTest Case(s):\n\n";

    val _ = print "convertToRealABS [10,~20,~30,~40,50,60];\n";
    convertToRealABS [10,~20,~30,~40,50,60];




(* Problem 6 - Use the function Reduce and an anonymous function to find the maximum of a list of reals. *)

val _ = print "\n\n\n\n\t\t\tProblem 6: \n\n";

(*compare each element one at a time with reduce, take the bigger element and return it at end*)
fun getMax(L) = Reduce(fn (x:real, y:real) => if x > y then x else y, L);

val _ = print "\n\n\tTest Case(s):\n\n";

val _ = print "getMax [10,~20,~30,~40,50,60];\n";
getMax [10.0,~20.0,~30.0,~40.0,50.0,60.0];



(*Problem 7 - Use the function Filter and an anonymous function to find those elements of a list of reals that are
between 10.0 and 20.0 (inclusive). *)

val _ = print "\n\n\n\n\t\t\tProblem 7: \n\n";

(*filter out elements that don't fit the lambda function useing filter function*)
fun filterToRange10to20 nil = nil
  | filterToRange10to20 (L) =
    Filter(fn x:real => x >= 10.0 andalso x<= 20.0, L);


val _ = print "\n\n\tTest Case(s):\n\n";

val _ = print "filterToRange10to20 [1.0, 9.99, 10.0, 10.1, 15.0, 19.99, 20.0, 20.1, 25.0];\n";
filterToRange10to20 [1.0, 9.99, 10.0, 10.1, 15.0, 19.99, 20.0, 20.1, 25.0];

val _ = print "\n\n--------------------------------------------------------------------------------------"
