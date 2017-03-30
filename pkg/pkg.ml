#!/usr/bin/env ocaml
#use "topfind"
#require "topkg"
open Topkg

let () =
  let cmd c os files =
    let ocamlbuild = Conf.tool "rebuild" os in
    OS.Cmd.run @@ Cmd.(ocamlbuild % "-use-ocamlfind"
                                  %% (v "-I" % "src")
                                  %% (v "-I" % "test")
                                  %% of_list files)
  in
  let build = Pkg.build ~cmd () in
  Pkg.describe "dockblock" ~build ~change_logs:[] ~licenses:[] ~readmes:[] @@ fun c ->
  Ok [
    Pkg.lib "pkg/META";
    Pkg.lib ~exts:(Exts.exts [".cmo"; ".cmx";".cmi"; ".cmt"; ".o"; ".cma"; ".cmxa"; ".a"]) "src/DockBlock" ~dst:"DockBlock";
    Pkg.lib ~exts:(Exts.exts [".native";]) "test/test" ~dst:"test";
  ]
