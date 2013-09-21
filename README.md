Context_Flag
============

This module provides integration between the Context and Flag modules.
When enabled it creates new Context conditions which are based on the value of a Flag.

Working
-------
* Node active flags
* Current user active flags
* Features export

Not working
-----------
* Current user inactive flags
* User profile active tags
* User profile inactive tags

Todo
----
* Node inactive flags (if used with another condition these seem to work), I've commented these out for the time being.
* Comment active flags (I'm not sure if this would be useful or not, I'm leaning towards no.)
* Comment inactive flags
* Entity active flags
* Entity inactive flags
* Should inactive flags be an option at all? I'm sure there's a potential use-case for them, but I'm not sure they're really useful.
* Contexts triggered by multiple flags operate as "OR" rather than "AND", add a configuration option to account for this?