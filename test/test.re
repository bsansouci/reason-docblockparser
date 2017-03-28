open OUnit2;

open DockBlock;

let exampleInput = [
  "/**",
  " * Words",
  " * ",
  " * @foo bar",
  " */",
  "words not in docblock",
  "",
  "even more words"
];

let test1 test_ctxt => {
  let result = DockBlock.parseBlock exampleInput;
  assert_equal "\nWords\n " result.text
};

let test2 test_ctxt => {
  let result = DockBlock.parseBlock exampleInput;
  let first = List.hd result.params;
  let (key, value) = first;
  assert_equal "foo" key;
  assert_equal "bar" value
};

let suite =
  "suite" >::: ["Pulls text from dockblock" >:: test1, "Pulls params from dockblock" >:: test2];

let () = run_test_tt_main suite;
