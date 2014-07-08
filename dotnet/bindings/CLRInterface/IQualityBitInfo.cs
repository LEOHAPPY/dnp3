﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DNP3.Interface
{
    public interface IQualityBitInfo
    {
        string GetLongLabel(int bit);

        string GetShortLabel(int bit);
    }

    class TypedQualityBitInfo : IQualityBitInfo
    {
        readonly Func<int, String> func;

        public TypedQualityBitInfo(Func<int, String> func)
        { 
            this.func = func;
        }

        public string GetLongLabel(int bit)
        {
            return func(bit);
        }


        string IQualityBitInfo.GetShortLabel(int bit)
        {
            return this.GetLongLabel(bit).Substring(0, 2);
        }
    }

    public static class QualityInfo
    {
        public static readonly IQualityBitInfo binary = new TypedQualityBitInfo(GetBinaryString);
        public static readonly IQualityBitInfo doubleBinary = new TypedQualityBitInfo(GetDoubleBitBinaryString);
        public static readonly IQualityBitInfo counter = new TypedQualityBitInfo(GetCounterString);
        public static readonly IQualityBitInfo analog = new TypedQualityBitInfo(GetAnalogString);
        public static readonly IQualityBitInfo binaryOutputStatus = new TypedQualityBitInfo(GetBinaryOutputStatusString);
        public static readonly IQualityBitInfo octetString = new TypedQualityBitInfo(x => "");

        public static IEnumerable<string> GetLongNames(byte flags, IQualityBitInfo info)
        {
            for (byte i = 0; i < 8; ++i)
            {
                if ((flags & (1 << i)) != 0)
                {
                    yield return info.GetLongLabel(i);
                }
            }
        }

        public static IEnumerable<string> GetShortNames(byte flags, IQualityBitInfo info)
        {
            for (byte i = 0; i < 8; ++i)
            {
                if ((flags & (1 << i)) != 0)
                {
                    yield return info.GetShortLabel(i);
                }
            }
        }
        
        static string GetBinaryString(int index)
        {
            return ((BinaryQuality) (1 << index)).ToString();
        }

        static string GetDoubleBitBinaryString(int index)
        {
            return ((DoubleBitBinaryQuality) (1 << index)).ToString();
        }

        static string GetCounterString(int index)
        {
            return ((CounterQuality)(1 << index)).ToString();
        }       

        static string GetAnalogString(int index)
        {
            return ((AnalogQuality)(1 << index)).ToString();
        }

        static string GetBinaryOutputStatusString(int index)
        {
            return ((BinaryOutputStatusQuality)(1 << index)).ToString();
        }
        
    }
}
