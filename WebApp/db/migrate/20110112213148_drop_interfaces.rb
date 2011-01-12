class DropInterfaces < ActiveRecord::Migration
  def self.up
	drop_table :interfaces
	remove_column :sensor_types, :interface_id
	add_column :sensors, :analog_port, :integer
  end

  def self.down
	create_table :interfaces do |t|
		t.integer :analog_port
		t.boolean :spi
		t.integer :station_id

		t.timestamps
    end
	add_column :sensor_types, :interface_id, :integer
	remove_column :sensors, :analog_port
  end
end
