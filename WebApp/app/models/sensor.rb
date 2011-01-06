class Sensor < ActiveRecord::Base
	belongs_to :station
	has_many :measured_datas
	has_one :sensor_type
end
