class MeasuredData < ActiveRecord::Base

	belongs_to :sensor
	
	validates :messdaten_int, :presence => true

end
