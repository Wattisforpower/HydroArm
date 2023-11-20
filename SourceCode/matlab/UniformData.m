function [Data] = UniformData(Samples, MaxVal, MinVal)

    range = MaxVal - MinVal;
    meanVal = (MaxVal + MinVal)/2;
    
    for i = 1:Samples
        Data(1, i) = range * (rand - 0.5) + meanVal;
        Data(2, i) = range * (rand - 0.5) + meanVal;
    end

end
