---@enum ProjectileMotionStyle
ProjectileMotionStyle = {
    Linear = 0;-- Goes forward by default. Uses the ProjectileSystem's `LinearSpeed` setting. Gravity does not take effect on this style.
    Lobbed = 1;-- Moves using the `Velocity` property. Gravity applies to this style.
    Spread = 2;-- Decelerates in the Y direction for the first few frames. Used by the Threepeater to make the peas go in different lanes at first. Gravity does not take effect on this style.
    Expiring = 5;-- Moves forward by default using `ProjectileSystem.LinearSpeed`, but expires when the projectile's age is more than `ProjectileSyste.ExpiryAge`.
    Backwards = 6;-- Moves backwards using `ProjectileSystem.LinearSpeed`. Gravity does not affect this style.
    Star = 7;-- Moves in a straight line that may or may not be directly forwards or backwards. Gravity does not affect this style.
    Homing = 9;-- Moves towards `TargetZombie`. Uses the velocity's magnitude as speed, and `ProjectileSystem.HomingSteer` to determine the maximum angle it can steer each frame.
};