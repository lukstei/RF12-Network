class MeasuredData < ActiveRecord::Base

	belongs_to :sensor
	
	validates :messdaten_int, :messzeit, :presence => true
	
	def self.total_mean_on(sensor, date)
		MeasuredData.where("date(messzeit)= ? AND sensor_id = ?", date, sensor.id).sum(:messdaten_int) / MeasuredData.where("date(messzeit)= ? AND sensor_id = ?", date, sensor.id).count
	end 

end
