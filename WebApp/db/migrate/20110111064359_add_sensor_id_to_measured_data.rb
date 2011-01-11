class AddSensorIdToMeasuredData < ActiveRecord::Migration
  def self.up
	add_column :measured_datas, :sensor_id, :integer
  end

  def self.down
	remove_column :measured_datas, :sensor_id
  end
end
