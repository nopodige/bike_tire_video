package com;

public class DynamicParameters
{
    private static DynamicParameters singleton = null;
    
    private float bikeWheelRateHz;
    
    public DynamicParameters()
    {
        singleton = this;
        setBikeWheelRate(Constants.WHEEL.defaultRateHz);
    }

    public static void setBikeWheelRate(float hz) {
        singleton.bikeWheelRateHz = hz;
    }
    
    public static float getBikeWheelRateHz() {
        return singleton.bikeWheelRateHz;
    }
}
