#pragma once

#include <blmc_can/blmc_can.h>

#include <memory>
#include <string>

#include <utils/timer.hpp>
#include <utils/threadsafe_timeseries.hpp>

#include <devices/device_interface.hpp>
#include <devices/motor_board.hpp>

class AnalogSensorInterface: public DeviceInterface
{
public:
    typedef ThreadsafeTimeseries<double> ScalarTimeseries;

    virtual std::shared_ptr<const ScalarTimeseries> measurement() const = 0;

    virtual ~AnalogSensorInterface() {}
};

class AnalogSensor: public AnalogSensorInterface
{
    std::shared_ptr<MotorBoardInterface> board_;
    size_t sensor_id_;

public:
    AnalogSensor(std::shared_ptr<MotorBoardInterface> board, bool sensor_id):
        board_(board),
        sensor_id_(sensor_id)
    { }

    virtual std::shared_ptr<const ScalarTimeseries> measurement() const
    {
        if(sensor_id_ == 0)
        {
            return board_->measurement(MotorBoardInterface::analog_0);
        }
        else
        {
            return board_->measurement(MotorBoardInterface::analog_1);
        }
    }

};