Context_Flag
============

This module provides integration between the Context and Flag modules.
When enabled it creates new Context conditions which are based on the value of a Flag.

Working
-------
* Node active flags
* Node inactive flags (if used with another condition these seem to work)
* Current user active flags

Not working
-----------
* Current user inactive flags
* User profile active tags
* User profile inactive tags

Todo
----
* Comment active flags (I'm not sure if this would be useful or not, I'm leaning towards no.)
* Comment inactive flags
* Entity active flags
* Entity inactive flags
* Should inactive flags be an option at all? I'm sure there's a potential use-case for them, but I'm not sure they're really useful.
* Make sure it works with Features.