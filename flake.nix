{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    fenix = {
      url = "github:nix-community/fenix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, flake-utils, fenix }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
        # mkShell = (pkgs.mkShell.override {
        #   stdenv = pkgs.gcc13Stdenv;
        # });
        # cc = pkgs.gcc13;
        mkShell = pkgs.mkShell;
        cc = pkgs.gcc;
        rust = fenix.packages.${system}.complete.withComponents [
          "rustc"
          "cargo"
          "clippy"
          "rustfmt"
          "rust-src"
          "rust-analyzer"
        ];
      in
      {
        devShell = mkShell {
          buildInputs = with pkgs; [
            cc
            rust
            python3

            gnumake
            # ninja
            # meson

            lldb
            clang-tools
          ];

          shellHook = ''
            PATH="${./bin}:$PATH"
          '';
        };
      }
    );
}
