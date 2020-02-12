% CIS 424 Project 4
% Brandon Kelley 2716916 & Paul Antonescu 2726151


% Problem 1 - define relations for specfied relations, test with family_tree.pl


  % (a) sibling
  sibling(Sibling_1, Sibling_2) :-

     not(Sibling_1 = Sibling_2),  % can't be sibling with themself

	   ((father(Father, Sibling_1),  % share same father
	   father(Father, Sibling_2));

	   (mother(Mother, Sibling_1),  % share same mother
	   mother(Mother, Sibling_2))).



  % (b) sister
  sister(Female, Sibling) :-

    female(Female), % must be female
    sibling(Female, Sibling). % must be sibling with them.



  % (c) uncle
  uncle(Uncle,Person) :-

    male(Uncle), % Uncle must be male

	  father(Father, Person), % get Father & Mother of the person
	  mother(Mother, Person),

	  (sibling(Uncle, Father);  % if Uncle is siblings with the persons Father or Mother, then he is their uncle.
    sibling(Uncle, Mother)).  %  *note* this does not cover uncle in-law by being the aunt's husband.



  % (d) grandson
  grandson(Grandson,Grandparent) :-

	   male(Grandson), % make sure Grandson is male

     % get father of grandson and grandparent is the grandson's father's mother or father.
	   ((father(Father, Grandson), (father(Grandparent, Father); mother(Grandparent, Father)));

    % OR get mother of grandson and grandparent is the grandson's mother's mother or father.
	   (mother(Mother, Grandson), (father(Grandparent, Mother);mother(Grandparent, Mother)))).




  % (e) descendant
  descendant(Person_1, Person_2) :-

	    (father(Person_2,Person_1); % person2 is father or mother of person 1, direct descendant (base case)
      mother(Person_2,Person_1));

      % person 2 is the grandparent of person 1 ,and person 1 has the granparents child as a parent (recursive case)
	    (father(Person_2, Child); mother(Person_2, Child)), descendant(Person_1, Child).




% Problem 2 - write rules to find the final element of a list.

%Function format: (List,Result)
getFinal([Final], Final). % base case, Final is the only item in the list
getFinal([Head|RemainingList], Element) :- getFinal(RemainingList, Element). % recursive case, use RemainingList as new list.




% Problem 3 - given the following grammar, implement a parser which recognizes sentences generated by this grammar.
% Nonterminals = S,X,Y,Z      Terminals = a,b,c

match(X,[X|T],T). % match function given in class

% <X> -> a <X> | a
x(Sentence, Remaining):-
      (match(a, Sentence, LeftOverAfterMatch), x(LeftOverAfterMatch, Remaining)); % a <X> OR
      match(a, Sentence, Remaining). % a

% <Y> -> b <Y> | b
y(Sentence,Remaining):-
      (match(b, Sentence, LeftOverAfterMatch), y(LeftOverAfterMatch, Remaining)); % b <Y> OR
      match(b, Sentence, Remaining). % b

% <Z> -> c <Z> | c
z(Sentence,Remaining):-
      (match(c, Sentence, LeftOverAfterMatch), z(LeftOverAfterMatch, Remaining)); % c <Z> OR
      match(c, Sentence, Remaining). % c

% <S> -> <X> <Y> <Z>      *note* moved to bottom as stated in class to avoid error
s(Sentence, Remaining):-
      x(Sentence, LeftOverAfterX), % Call X(), pass Remaining to Y()
      y(LeftOverAfterX, LeftOverAfterY), % Call Y(), pass Remaining to Z ()
      z(LeftOverAfterY, Remaining). % Call Z(), list should be empty




% Problem 4 - complete the example dem_candidate in the textbook, use trace to show backtracking can be reduced with cut

% make our own tests and dataset, assume no duplicates in dataset

  % top 3 current democratic candidates = Biden, Warren, Sanders    these people should pass the tests
  % 3 unelgible democratic candiates = Trump (republican) so not a memeber, Obama already served two terms, and
  % (baker) mayfield not over 35 (I will assume he is a democrat for this example). these people should fail the tests

canidateList([biden, warren, sanders, trump, obama, mayfield]).

% define democrats of canidateList, note trump is left out
democrat([biden, warren, sanders, obama, mayfield]).

% define people with remaining Presidental terms, note obama is left out
remainingTerms([biden, warren, sanders, trump, mayfield]).

% define people over 35 years of age, note that mayfield is left out
over35([biden, warren, sanders, trump, obama]).


% create tests Function

tests(DemocraticPresidentalCandidate):-
  over35(Age35), % get over35 list
  member(DemocraticPresidentalCandidate, Age35), % over 35 years old
  democrat(DemParty), % get democrat list
  member(DemocraticPresidentalCandidate, DemParty), % must be a democrat
  remainingTerms(RemTerms), % get hasRemainingTerms list
  member(DemocraticPresidentalCandidate, RemTerms). % must have remainging terms



% given in class, show diffrence with and without cut (!) in member
member(Elm, [Elm|_]):-!.
member(Elm, [_|L]):- member(Elm, L).
dem_candidate(X):- member(X, Democrat), tests(X).