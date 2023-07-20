{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
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
      in
      {
        devShell = mkShell {
          buildInputs = with pkgs; [
            cc
            gnumake
            # ninja
            # meson

            gdb
            clang-tools

            python3
          ];

          shellHook = ''
            PATH="${./bin}:$PATH"
          '';
        };
      }
    );
}
