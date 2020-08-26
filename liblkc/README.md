# liblkc

Linux kernel configuration system (Kconfig) C library.

This library can be used to programmatically parse the configuration
definition files (`Kconfig`), load configuration value files (`.config`),
obtain the configuration options including their types and values, and perform
most of the non-interactive configuration manipulations supported by the
`kconfig-conf` configurator.

Note that the library uses global state and is therefore not thread-safe.
