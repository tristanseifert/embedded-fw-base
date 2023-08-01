# nanopb

A minimal, C language implementation of
[Google Protocol Buffers](https://protobuf.dev) for embedded use.

See the [nanopb homepage](https://jpa.kapsi.fi/nanopb/) for more information.

## Building protobuf definitions

This library exports the path to the nanopb-specific schema plugin for `protoc`
as `EFWB_NANOPB_GENERATOR`.
