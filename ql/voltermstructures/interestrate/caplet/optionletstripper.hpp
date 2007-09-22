/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2007 Ferdinando Ametrano
 Copyright (C) 2007 Fran�ois du Vignaud
 Copyright (C) 2007 Katiuscia Manzoni

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file optionletstripper.hpp
    \brief optionlet (cap/floor) volatility stripper
*/

#ifndef quantlib_optionletstripper_hpp
#define quantlib_optionletstripper_hpp

#include <ql/patterns/lazyobject.hpp>
#include <ql/instruments/capfloor.hpp>
#include <ql/voltermstructures/interestrate/cap/capfloortermvolsurface.hpp>
#include <ql/math/matrix.hpp>
#include <vector>

namespace QuantLib {
    class IborIndex;
    class YieldTermStructure;
    class CapFloorTermVolSurface;
    class DayCounter;
    class Calendar;

    typedef std::vector<std::vector<boost::shared_ptr<CapFloor> > > CapFloorMatrix;

    class OptionletStripper : public LazyObject {
      public:
        OptionletStripper(const boost::shared_ptr<CapFloorTermVolSurface>& surface,
                          const boost::shared_ptr<IborIndex>& index,
                          const std::vector<Rate>& switchStrikes);
        //! \name Cap Stripper interface
        //@{
        const Matrix& capFloorPrices() const;
        const Matrix& capFloorVolatilities() const;

        const Matrix& optionletPrices() const;
        const Matrix& optionletVolatilities() const;
        const std::vector<Rate>& strikes() const;

        const std::vector<Period>& optionletTenors() const;
        const std::vector<Date>& optionletDates() const;
        const std::vector<Time>& optionletTimes() const;

        const std::vector<Date>& optionletPaymentDates() const;

        boost::shared_ptr<CapFloorTermVolSurface> surface() const;
        //@}
        //! \name LazyObject interface
        //@{
        void performCalculations () const;
        //@}
      private:
        const boost::shared_ptr<CapFloorTermVolSurface> surface_;
        const boost::shared_ptr<IborIndex> index_;
        Size nStrikes_;
        std::vector<Period> optionletTenors_;
        Size nOptionletTenors_;
        mutable Matrix capFloorPrices_, optionletPrices_;
        mutable Matrix capFloorVols_, optionletVols_;
        mutable Matrix optionletStDevs_;
        mutable std::vector<Rate> atmOptionletRate_;
        mutable std::vector<Date> optionletDates_;
        mutable std::vector<Date> optionletPaymentDates_;
        mutable std::vector<Time> optionletAccrualPeriods_;
        mutable std::vector<Time> optionletTimes_;
        std::vector<Period> capFloorLengths_;
        mutable CapFloorMatrix capFloors_;
        std::vector<Rate> switchStrikes_;
    };

    inline const Matrix& OptionletStripper::optionletPrices() const {
        calculate();
        return optionletPrices_;
    }

    inline const Matrix& OptionletStripper::optionletVolatilities() const {
        calculate();
        return optionletVols_;
    }

    inline const Matrix& OptionletStripper::capFloorPrices() const {
        calculate();
        return capFloorPrices_;
    }

    inline const Matrix& OptionletStripper::capFloorVolatilities() const {
        calculate();
        return capFloorVols_;
    }

    inline
    const std::vector<Period>& OptionletStripper::optionletTenors() const {
        return optionletTenors_;
    }

    inline
    const std::vector<Date>& OptionletStripper::optionletDates() const {
        calculate();
        return optionletDates_;
    }
     
    inline
    const std::vector<Date>& OptionletStripper::optionletPaymentDates() const {
        calculate();
        return optionletPaymentDates_;
    }
     
    inline
    const std::vector<Time>& OptionletStripper::optionletTimes() const {
        calculate();
        return optionletTimes_;
    }

}

#endif